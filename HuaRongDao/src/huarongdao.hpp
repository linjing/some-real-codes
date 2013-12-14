#ifndef HUARONGDAO_HPP 
#define HUARONGDAO_HPP

#include <cstring>
#include <deque>
#include <list>
#include <memory>
#include <string>
#include <vector>

const int max_row = 5;
const int max_col = 4;
const int chess_number = 10;

class chessboard;
class chess;

struct point {
  point () : row (0), col (0) {}
  point (int r, int c) : row (r), col (c) {}
  int row;
  int col;
};

struct board_map {
  int board_[max_row][max_col];
  board_map () {
    memset (&board_, 0, max_col * max_row * sizeof (int) );
  }
};

enum chess_type {
  cao_cao, guan_yu, zhang_fei, zhao_yun, ma_chao, huang_zhong, zu
};

struct chess_sample_id {
  int width;
  int height;
  int key;
};

struct chess_id {
  chess_type type;
  int width;
  int height;
  int key;
  std::string info;
};

struct chess_id get_chess (chess_type type);
struct chess_sample_id get_sample_chess (chess_type type);

class chess {
public:
  chess (chess_type type, point p)
    : pos_ (p)
    { id_ = get_sample_chess (type); }
public:
  std::string to_mask () const;
  virtual int key () const { return id_.key; }
  void fill_board (board_map &board) const;
public:
  point pos_;
  chess_sample_id id_;
};

//enum direction {
//  up, down, right, left
//};


class chessboard {
public:
  std::vector<chess> chesses;
  struct board_map board_;
  void push_chess (chess &c);
  bool is_solved () const;
  void show () const;
  std::deque<chessboard> can_move_steps () const;

  int steps;
};

struct board_mask {
  struct board_map board;
  board_mask (chessboard &chesses);
  std::string get_mask () const;
  size_t get_hash () const;
};

namespace std {
  template <>
  struct hash<board_mask> {
    size_t operator () (const board_mask&m) const {
      return m.get_hash ();
    }
  };
}

struct board_mask_less {
  bool operator () (const board_mask &l, const board_mask &r) {
    return l.get_mask () < r.get_mask ();
  }
};

bool operator == (const board_mask &l, const board_mask &r);
bool operator < (const board_mask &l, const board_mask &r);

//class chessboard {
//public:
//  void init_chess (chess &c, point &p) {};
//public:
//  virtual void move (chess &c, const direction &d) = 0;
//private:
//  chessboard chesses_;
//  board_map board_;
//};

#endif
