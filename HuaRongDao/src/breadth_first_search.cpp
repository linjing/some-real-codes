#include "huarongdao.hpp"

#include <deque>
#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

int main () {
  set<board_mask> seen; // add known
  //unordered_set<board_mask> seen; // add known
  // error: static assertion failed: std::hash is not specialized for this type 
  deque<chessboard> queue;

  // input init 
  chesses_t init_chesses;

  shared_ptr<chess> gy (new guan_yu (point (2, 1)));
  init_chesses.push_back (gy);
  shared_ptr<chess> zf (new zhang_fei (point (0, 0)));
  init_chesses.push_back (zf);
  shared_ptr<chess> zy (new zhao_yun (point (0, 3)));
  init_chesses.push_back (zy);
  shared_ptr<chess> mc (new ma_chao (point (2, 0)));
  init_chesses.push_back (mc);
  shared_ptr<chess> hz (new huang_zhong (point (2, 3)));
  init_chesses.push_back (hz);

  shared_ptr<chess> cc (new huang_zhong (point (0, 1)));
  init_chesses.push_back (cc);

  shared_ptr<chess> z1 (new zu (point (4, 0)));
  init_chesses.push_back (z1);
  shared_ptr<chess> z2 (new zu (point (3, 1)));
  init_chesses.push_back (z2);
  shared_ptr<chess> z3 (new zu (point (3, 2)));
  init_chesses.push_back (z3);
  shared_ptr<chess> z4 (new zu (point (4, 3)));
  init_chesses.push_back (z4);

  queue.push_back (init_chesses);
  board_mask bm (init_chesses);
  seen.insert (bm);

  // BFS to results
  bool is_solved = false;
  while (!queue.empty ()) {
    const chesses_t curr = queue.front ();
    queue.pop_front ();

    if (curr.is_solved ()) {
      is_solved = true;
      break; // donw here 
    }

    auto move_move_res = curr.can_move_steps ();
    for (auto res : move_move_res) {
      board_mask bm (res);
      if (seen.find (bm) == seen.end ())
        continue;
      seen.insert (bm);
      queue.push_back (res);
    }
  }

  cout << " " <<  is_solved << endl;

  return 0;
}
