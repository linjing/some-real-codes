#include "huarongdao.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/functional/hash/hash.hpp>

using namespace std;

size_t board_map::get_hash () const {
  const uint8_t *p = &board[0];
  return boost::hash_range (p, p+board_size);
}

bool operator == (const board_map &l, const board_map &r) {
  return memcmp ((char*)&l.board[0], &r.board[0], board_size*sizeof (uint8_t)) == 0;
}

bool operator < (const board_map &l, const board_map &r) {
  return memcmp ((char*)&l.board[0], &r.board[0], board_size*sizeof (uint8_t)) < 0;
}

inline uint8_t to_pos (uint8_t row, uint8_t col) {
  return row * max_col + col;
}

std::string board_map::get_mask () const {
  ostringstream oss;
  for (int i = 0; i < board_size; ++i)
    oss << (int) board[i] << ",";
  return oss.str ();
}

string chess::to_mask () const {
  ostringstream oss;
  oss << (int) key () << (int) pos_.get ();
  return oss.str ();
}

void chess::fill_board (board_map &board) const {
  for (int r = 0; r < height (); ++r)
    for (int c = 0; c < width (); ++c) {
      // cout << "board.board_[" << pos_.row + r << "][" << pos_.col + c << "]" << endl;
      assert (board.board[to_pos (pos_.row () + r, pos_.col () + c)] == 0);
      board.board[to_pos (pos_.row () + r, pos_.col () + c)] = this->key ();
    }
}

void chessboard::push_chess (chess &c) {
  chesses.push_back (c);
  c.fill_board (board_);
  steps = 0;
}

bool chessboard::is_solved () const {
  static const uint8_t caocao_key = 1;
  static const int p1 = 4 * max_col + 1;
  static const int p2 = 4 * max_col + 2;
  //if (board_.board_[4][1] == caocao_key && board_.board_[4][2] == caocao_key)
  if (board_.board[p1] == caocao_key && board_.board[p2] == caocao_key)
    return true;
  return false;
}
/*
         DOWN/Bottom
LEFT               Right
         UP/Top
<--   width ------------>
^
|
height
|
V
   col: 0, 1, 2, 3
row 0:
row 1:
row 2:
row 3:
row 4:
*/

inline int right (const chess &c) {
  return c.pos_.col () + c.width () - 1;
}
inline int left (const chess &c) {
  return c.pos_.col ();
}
inline int bottom (const chess &c) {
  return c.pos_.row ();
}

inline int top (const chess &c) {
  return c.pos_.row () + c.height () - 1;
}

bool can_to_right (const chess &c, const board_map &board) {
  int dest_col = right(c) + 1;
  if (dest_col >= max_col)
    return false;
  for (int r = bottom (c); r <= top(c); ++r) {
    if (board.board[to_pos (r, dest_col)] != 0)
      return false;
  }
  return true;
}

bool can_to_left (const chess &c, const board_map &board) {
  int dest_col = left(c) - 1;
  if (dest_col < 0)
    return false;
  for (int r = bottom (c); r <= top(c); ++r) {
    if (board.board[to_pos (r, dest_col)] != 0)
      return false;
  }
  return true;
}

bool can_to_up (const chess &c, const board_map &board) {
  int dest_row = top (c) + 1;
  if (dest_row >= max_row)
    return false;
  for (int col = left (c);  col <= right (c); ++col) {
    if (board.board[to_pos (dest_row, col)] != 0)
      return false;
  }
  return true;
}

bool can_to_down (const chess &c, const board_map &board) {
  int dest_row = bottom (c) - 1;
  if (dest_row < 0)
    return false;
  for (int col = left (c);  col <= right (c); ++col) {
    if (board.board[to_pos (dest_row, col)] != 0)
      return false;
  }
  return true;
}

void move_down (const chess &c, board_map &board, vector<chess> &chesses) {
  assert (can_to_down (c, board));
  int dest_row = bottom (c) - 1;
  int from_row = top (c);

  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (it->pos_ == c.pos_)
      it->pos_.down ();
  }

  for (int col = left (c);  col <= right (c); ++col) {
    board.board[to_pos (dest_row, col)] = c.key ();
    board.board[to_pos (from_row, col)] = 0;
  }
}

void move_up (const chess &c, board_map &board, vector<chess> &chesses) {
  assert (can_to_up (c, board));
  int dest_row = top (c) + 1;
  int from_row = bottom (c);

  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (it->pos_ == c.pos_)
      it->pos_.up ();
  }

  for (int col = left (c);  col <= right (c); ++col) {
    board.board[to_pos (dest_row, col)] = c.key ();
    board.board[to_pos (from_row, col)] = 0;
  }
}

void move_left (const chess &c, board_map &board, vector<chess> &chesses) {
  assert (can_to_left (c, board));
  int dest_col = left (c) - 1;
  int from_col = right (c);

  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (it->pos_ == c.pos_)
      it->pos_.left ();
  }

  for (int row = bottom (c);  row <= top (c); ++row) {
    board.board[to_pos (row, dest_col)] = c.key ();
    board.board[to_pos (row, from_col)] = 0;
  }
}

void move_right (const chess &c, board_map &board, vector<chess> &chesses) {
  assert (can_to_right (c, board));
  int dest_col = right (c) + 1;
  int from_col = left (c);

  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (it->pos_ == c.pos_)
      it->pos_.right ();
  }

  for (int row = bottom (c);  row <= top (c); ++row) {
    board.board[to_pos (row, dest_col)] = c.key ();
    board.board[to_pos (row, from_col)] = 0;
  }
}

struct chess_info {
  uint8_t key;
  uint8_t width;
  uint8_t height;
  chess_type type;
  std::string info;
  chess_info () {}
  chess_info (uint8_t width, uint8_t height, uint8_t key, chess_type type, string info) {
    this->width = width;
    this->height = height;
    this->key = key;
    this->type = type;
    this->info = info;
  }
};

class chess_static_info {
  public:
    static const int chess_type_number = 5;
    static chess_info chess_table[chess_type_number];
};

chess_info chess_static_info::chess_table[chess_type_number] = {
  {1, 1, 4, chess_type::zu, "zu"}, // FIXME not used
  {2, 2, 1, chess_type::cao_cao, "cao_cao"},
  {2, 1, 2, chess_type::guan_yu, "guan_yu"},
  {1, 2, 3, chess_type::w1_h2, "w1_h2"},
  {1, 1, 4, chess_type::zu, "zu"}
};

uint8_t chess_width (const chess_type &type) {
  return chess_static_info::chess_table[(int) type].width;
}

uint8_t chess_height (const chess_type &type) {
  return chess_static_info::chess_table[(int) type].height;
}

void chessboard::show () const {
  for (int r = 0; r < max_row; ++r) {
    for (int c = 0; c < max_col; ++c)
      printf (" %02d ", (int) board_.board[to_pos (r,c)]);
    cout << endl;
  }
}
