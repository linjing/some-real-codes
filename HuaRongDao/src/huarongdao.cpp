#include "huarongdao.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/functional/hash/hash.hpp>

using namespace std;

board_mask::board_mask (const chessboard &chesses)
  : board (chesses.board_) 
{}

size_t board_mask::get_hash () const {
  const uint8_t *p = &board.board_[0];
  return boost::hash_range (p, p+board_size);
}

bool operator == (const board_mask &l, const board_mask &r) {
  return memcmp ((char*)&l.board.board_[0], &r.board.board_[0], board_size*sizeof (uint8_t)) == 0;
}

bool operator < (const board_mask &l, const board_mask &r) {
  return memcmp ((char*)&l.board.board_[0], &r.board.board_[0], board_size*sizeof (uint8_t)) < 0;
}

bool operator == (const point &l, const point &r) {
  return l.pos == r.pos;
}

inline uint8_t to_pos (uint8_t row, uint8_t col) {
  return row * max_col + col;
}

std::string board_mask::get_mask () const {
  ostringstream oss;
  for (int i = 0; i < board_size; ++i)
    oss << (int) board.board_[i] << ",";
  return oss.str ();
}

string chess::to_mask () const {
  ostringstream oss;
  oss << id_.width << id_.height << (int) pos_.row () << (int) pos_.col ();
  return oss.str ();
}


void chess::fill_board (board_map &board) const {
  for (int r = 0; r < id_.height; ++r)
    for (int c = 0; c < id_.width; ++c) {
      // cout << "board.board_[" << pos_.row + r << "][" << pos_.col + c << "]" << endl;
      assert (board.board_[to_pos (pos_.row () + r, pos_.col () + c)] == 0);
      board.board_[to_pos (pos_.row () + r, pos_.col () + c)] = this->key ();
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
  if (board_.board_[p1] == caocao_key && board_.board_[p2] == caocao_key)
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
  return c.pos_.col () + c.id_.width - 1;
}
inline int left (const chess &c) {
  return c.pos_.col ();
}
inline int bottom (const chess &c) {
  return c.pos_.row ();
}

inline int top (const chess &c) {
  return c.pos_.row () + c.id_.height - 1;
}

bool can_to_right (const chess &c, const board_map &board) {
  int dest_col = right(c) + 1;
  if (dest_col >= max_col)
    return false;
  for (int r = bottom (c); r <= top(c); ++r) {
    if (board.board_[to_pos (r, dest_col)] != 0)
      return false;
  }
  return true;
}

bool can_to_left (const chess &c, const board_map &board) {
  int dest_col = left(c) - 1;
  if (dest_col < 0)
    return false;
  for (int r = bottom (c); r <= top(c); ++r) {
    if (board.board_[to_pos (r, dest_col)] != 0)
      return false;
  }
  return true;
}

bool can_to_up (const chess &c, const board_map &board) {
  int dest_row = top (c) + 1;
  if (dest_row >= max_row)
    return false;
  for (int col = left (c);  col <= right (c); ++col) {
    if (board.board_[to_pos (dest_row, col)] != 0)
      return false;
  }
  return true;
}

bool can_to_down (const chess &c, const board_map &board) {
  int dest_row = bottom (c) - 1;
  if (dest_row < 0)
    return false;
  for (int col = left (c);  col <= right (c); ++col) {
    if (board.board_[to_pos (dest_row, col)] != 0)
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
    board.board_[to_pos (dest_row, col)] = c.id_.key;
    board.board_[to_pos (from_row, col)] = 0;
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
    board.board_[to_pos (dest_row, col)] = c.id_.key;
    board.board_[to_pos (from_row, col)] = 0;
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
    board.board_[to_pos (row, dest_col)] = c.id_.key;
    board.board_[to_pos (row, from_col)] = 0;
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
    board.board_[to_pos (row, dest_col)] = c.id_.key;
    board.board_[to_pos (row, from_col)] = 0;
  }
}

std::deque<chessboard> chessboard::can_move_steps () const {
  std::deque<chessboard> res;
  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (can_to_down (*it, board_)) {
      chessboard board (*this);
      move_down (*it, board.board_, board.chesses);
      board.steps ++;
      res.push_back (board);
    }
    if (can_to_up (*it, board_)) {
      chessboard board (*this);
      move_up (*it, board.board_, board.chesses);
      board.steps ++;
      res.push_back (board);
    }
    if (can_to_right (*it, board_)) {
      chessboard board (*this);
      move_right (*it, board.board_, board.chesses);
      board.steps ++;
      res.push_back (board);
    }
    if (can_to_left (*it, board_)) {
      chessboard board (*this);
      move_left (*it, board.board_, board.chesses);
      board.steps ++;
      res.push_back (board);
    }
  }
  return res;
}

struct chess_sample_id get_sample_chess (chess_type type) {
  chess_sample_id id;
  switch (type) {
    case chess_type::cao_cao:
      id.width = 2; id.height = 2; id.key = 1;
      break;
    case chess_type::guan_yu:
      id.width = 2; id.height = 1; id.key = 10;
      break;
    case chess_type::zhang_fei:
    case chess_type::zhao_yun:
    case chess_type::ma_chao:
    case chess_type::huang_zhong:
      id.width = 1; id.height = 2; id.key = 11;
      break;
    case chess_type::zu:
      id.width = 1; id.height = 1; id.key = 21;
      break;
  }
  return id;
}

struct chess_id get_chess (chess_type type) {
  chess_id id;
  switch (type) {
    case chess_type::cao_cao:
      id.width = 2; id.height = 2; id.key = 1; id.info = "cao_cao";
      id.type = type;
      break;
    case chess_type::guan_yu:
      id.width = 2; id.height = 1; id.key = 11; id.info = "guan_yu";
      id.type = type;
      break;
    case chess_type::zhang_fei:
      id.width = 1; id.height = 2; id.key = 12; id.info = "zhang_fei";
      id.type = type;
      break;
    case chess_type::zhao_yun:
      id.width = 1; id.height = 2; id.key = 13; id.info = "zhao_yun";
      id.type = type;
      break;
    case chess_type::ma_chao:
      id.width = 1; id.height = 2; id.key = 14; id.info = "ma_chao";
      id.type = type;
      break;
    case chess_type::huang_zhong:
      id.width = 1; id.height = 2; id.key = 15; id.info = "huang_zhong";
      id.type = type;
      break;
    case chess_type::zu:
      id.width = 1; id.height = 1; id.key = 21; id.info = "zu";
      id.type = type;
      break;
  }
  return id;
}

void chessboard::show () const {
  for (int r = 0; r < max_row; ++r) {
    for (int c = 0; c < max_col; ++c)
      printf (" %02d ", (int) board_.board_[to_pos (r,c)]);
    cout << endl;
  }
}
