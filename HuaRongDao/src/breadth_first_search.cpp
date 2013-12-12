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
  chessboard init_chesses;

  chess gy (chess_type::guan_yu, point (2, 1));
  init_chesses.push_chess (gy);
  chess zf (chess_type::zhang_fei, point (0, 0));
  init_chesses.push_chess (zf);
  chess zy (chess_type::zhao_yun, point (0, 3));
  init_chesses.push_chess (zy);
  chess mc (chess_type::ma_chao, point (2, 0));
  init_chesses.push_chess (mc);
  chess hz (chess_type::huang_zhong, point (2, 3));
  init_chesses.push_chess (hz);

  chess cc (chess_type::cao_cao, point (0, 1));
  init_chesses.push_chess (cc);

  chess z1 (chess_type::zu, point (4, 0));
  init_chesses.push_chess (z1);
  chess z2 (chess_type::zu, point (3, 1));
  init_chesses.push_chess (z2);
  chess z3 (chess_type::zu, point (3, 2));
  init_chesses.push_chess (z3);
  chess z4 (chess_type::zu, point (4, 3));
  init_chesses.push_chess (z4);

  queue.push_back (init_chesses);
  board_mask bm (init_chesses);
  seen.insert (bm);

  // BFS to results
  bool is_solved = false;
  while (!queue.empty ()) {
    const chessboard curr = queue.front ();
    queue.pop_front ();
    cout <<  " curr "  << endl;
    curr.show ();

    if (curr.is_solved ()) {
      is_solved = true;
      break; // donw here 
    }

    auto move_res = curr.can_move_steps ();
    cout << move_res.size () << endl;
    for (auto res : move_res) {
      cout <<  " move result" << endl;
      res.show ();
      board_mask bm (res);
      if (seen.find (bm) != seen.end ())
        continue;
      seen.insert (bm);
      queue.push_back (res);
    }
  }

  cout << " " <<  is_solved << endl;

  return 0;
}
