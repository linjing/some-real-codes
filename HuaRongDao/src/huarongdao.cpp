#include "huarongdao.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

board_mask::board_mask (chesses_t &chesses) {
  auto css = chesses.chesses;
  ostringstream oss;
  for (auto c : css)
    oss << c.to_mask () << ";";
  mask = oss.str ();
}

bool operator == (const board_mask &l, const board_mask &r) {
  return l.get_mask () == r.get_mask ();
}

bool operator < (const board_mask &l, const board_mask &r) {
  return l.get_mask () < r.get_mask ();
}

string chess::to_mask () const {
  ostringstream oss;
  oss << id_.width << id_.height << pos_.row << pos_.col;
  return oss.str ();
}

void chess::fill_board (board_map &board) const {
  for (int r = 0; r < id_.height; ++r)
    for (int c = 0; c < id_.width; ++c) {
      // cout << "board.board_[" << pos_.row + r << "][" << pos_.col + c << "]" << endl;
      assert (board.board_[pos_.row + r][pos_.col + c] == 0);
      board.board_[pos_.row + r][pos_.col + c] = this->key ();
    }
}

void chessboard::push_chess (chess &c) {
  chesses.push_back (c);
  c.fill_board (board_);
}

bool chessboard::is_solved () const {
  static int caocao_key = 1;
  if (board_.board_[4][1] == caocao_key && board_.board_[4][2] == caocao_key)
    return true;
  return false;
}

std::deque<chessboard> chessboard::can_move_steps () const {
  std::deque<chessboard> res;
  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    
  }
  return res;
}

struct chess_id get_chess (chess_type type) {
  chess_id id;
  switch (type) {
    case chess_type::cao_cao:
      id.width = 2; id.height = 2; id.key = 1; id.info = "cao_cao";
      id.type = type;
      break;
    case chess_type::guan_yu:
      id.width = 2; id.height = 1; id.key = 10; id.info = "guan_yu";
      id.type = type;
      break;
    case chess_type::zhang_fei:
      id.width = 1; id.height = 2; id.key = 10; id.info = "zhang_fei";
      id.type = type;
      break;
    case chess_type::zhao_yun:
      id.width = 1; id.height = 2; id.key = 10; id.info = "zhao_yun";
      id.type = type;
      break;
    case chess_type::ma_chao:
      id.width = 1; id.height = 2; id.key = 10; id.info = "ma_chao";
      id.type = type;
      break;
    case chess_type::huang_zhong:
      id.width = 1; id.height = 2; id.key = 10; id.info = "huang_zhong";
      id.type = type;
      break;
    case chess_type::zu:
      id.width = 1; id.height = 1; id.key = 10; id.info = "zu";
      id.type = type;
      break;
  }
}
