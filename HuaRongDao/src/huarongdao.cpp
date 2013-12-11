#include "huarongdao.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

board_mask::board_mask (chesses_t &chesses) {
  auto css = chesses.chesses;
  ostringstream oss;
  for (auto c : css)
    oss << c->to_mask () << ";";
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
  oss << width_ << height_ << pos_.row << pos_.col;
  return oss.str ();
}

void chess::fill_board (board_map &board) const {
  for (int r = 0; r < height_; ++r)
    for (int c = 0; c < width_; ++c) {
      // cout << "board.board_[" << pos_.row + r << "][" << pos_.col + c << "]" << endl;
      assert (board.board_[pos_.row + r][pos_.col + c] == 0);
      board.board_[pos_.row + r][pos_.col + c] = this->key ();
    }
}

void chessboard::push_chess (std::shared_ptr<chess> &c) {
  chesses.push_back (c);
  c->fill_board (board_);
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
