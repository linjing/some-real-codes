#include "huarongdao.hpp"

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
