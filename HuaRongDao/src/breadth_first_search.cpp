#include "huarongdao.hpp"
#include "huarongdao_impl.hpp"

#include <deque>
#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

void init_board (chessboard &input_board) {
  chess gy (chess_type::guan_yu, point (2, 1));
  input_board.push_chess (gy);
  chess zf (chess_type::zhang_fei, point (0, 0));
  input_board.push_chess (zf);
  chess zy (chess_type::zhao_yun, point (0, 3));
  input_board.push_chess (zy);
  chess mc (chess_type::ma_chao, point (2, 0));
  input_board.push_chess (mc);
  chess hz (chess_type::huang_zhong, point (2, 3));
  input_board.push_chess (hz);

  chess cc (chess_type::cao_cao, point (0, 1));
  input_board.push_chess (cc);

  chess z1 (chess_type::zu, point (4, 0));
  input_board.push_chess (z1);
  chess z2 (chess_type::zu, point (3, 1));
  input_board.push_chess (z2);
  chess z3 (chess_type::zu, point (3, 2));
  input_board.push_chess (z3);
  chess z4 (chess_type::zu, point (4, 3));
  input_board.push_chess (z4);
}

int main () {
  unordered_set<board_map> seen; // add known board
  deque<chessboard> queue;

  // init, fill chess to board
  chessboard input_board;
  init_board (input_board);

  queue.push_back (input_board);
  seen.insert (input_board.board_);

  // BFS to results
  bool is_solved = false;
  while (!queue.empty ()) {
    const chessboard curr = queue.front ();
    queue.pop_front ();
#ifdef DEBUG
    cout <<  " curr "  << endl;
    curr.show ();
#endif

    if (curr.is_solved ()) {
      is_solved = true;
      cout << "steps " << curr.steps << endl;
      break; // down here
    }

    curr.move ([&seen, &queue] (const chessboard &next) {
      if (seen.find (next.board_) == seen.end ()) {
#ifdef DEBUG
        cout << "mask: " << bm.get_mask () << endl;
#endif
        queue.push_back (next);
        seen.insert (next.board_);
      }
    });
  }

  cout << " " <<  is_solved << endl;

  return 0;
}
