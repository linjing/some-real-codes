#include "huarongdao.hpp"

#include <type_traits>
#include <vector>

void move_right (const chess &c, board_map &board, std::vector<chess> &chesses);
void move_left (const chess &c, board_map &board, std::vector<chess> &chesses);
void move_up (const chess &c, board_map &board, std::vector<chess> &chesses);
void move_down (const chess &c, board_map &board, std::vector<chess> &chesses);

bool can_to_right (const chess &c, const board_map &board);
bool can_to_left (const chess &c, const board_map &board);
bool can_to_down (const chess &c, const board_map &board);
bool can_to_up (const chess &c, const board_map &board);
template <typename append_next_step>
void chessboard::move (const append_next_step &func) const {
  static_assert(
      std::is_convertible<append_next_step, std::function<void(const chessboard&)>>::value,
      "func must be callable with a 'const chessboard&' parameter.");
  for (auto it = chesses.begin (); it != chesses.end (); ++it) {
    if (can_to_down (*it, board_)) {
      chessboard board (*this);
      move_down (*it, board.board_, board.chesses);
      board.steps ++;
      func (board);
    }
    if (can_to_up (*it, board_)) {
      chessboard board (*this);
      move_up (*it, board.board_, board.chesses);
      board.steps ++;
      func (board);
    }
    if (can_to_right (*it, board_)) {
      chessboard board (*this);
      move_right (*it, board.board_, board.chesses);
      board.steps ++;
      func (board);
    }
    if (can_to_left (*it, board_)) {
      chessboard board (*this);
      move_left (*it, board.board_, board.chesses);
      board.steps ++;
      func (board);
    }
  }
}
