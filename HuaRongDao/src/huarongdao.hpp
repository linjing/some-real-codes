#ifndef HUARONGDAO_HPP 
#define HUARONGDAO_HPP

#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

const int max_row = 5;
const int max_col = 4;
const int chess_number = 10;
const int board_size = max_row * max_col;

class chessboard;
class chess;

struct point {
  point () : pos (0) {}
  point (uint8_t r, uint8_t c) { pos = (r << 4) + c; }
  inline uint8_t row () const { return pos >> 4;}
  inline uint8_t col () const { return pos & 15;}
  inline void down () { pos -= 16;}
  inline void up () {pos += 16;}
  inline void left () {pos -= 1;}
  inline void right () {pos += 1;}
  uint8_t pos; // rrrrcccc
};

struct board_map {
  uint8_t board_[board_size];
  board_map () {
    memset (&board_, 0, board_size * sizeof (uint8_t));
  }
};

enum chess_type {
  cao_cao, guan_yu, zhang_fei, zhao_yun, ma_chao, huang_zhong, zu
};

struct chess_id {
  uint8_t chess; // kkkkwwhh
#ifdef DEBUG
  chess_type type;
  std::string info;
#endif
  chess_id () : chess (0) {
    //std::cout << "c1:" << (int) chess << std::endl;
    }
  chess_id (uint8_t width, uint8_t height, uint8_t key) {
    chess = (key << 4) + (width << 2) + height;
    // std::cout << "c2:" << (int) chess << std::endl;
  }
  inline uint8_t key () const { return chess >> 4; }
  inline uint8_t width () const { return (chess >> 2) & 3; }
  inline uint8_t height () const { return chess & 3; }
};

struct chess_id get_chess (chess_type type);

class chess {
public:
  chess (chess_type type, point p)
    : pos_ (p)
    { id_ = get_chess (type); }
public:
  std::string to_mask () const;
  int key () const { return id_.key (); }
  void fill_board (board_map &board) const;
public:
  point pos_;
  chess_id id_;
};

//enum direction {
//  up, down, right, left
//};


class chessboard {
public:
  std::vector<chess> chesses;
  struct board_map board_;
  int steps;
public:
  void push_chess (chess &c);
  bool is_solved () const;
  void show () const;
  std::deque<chessboard> can_move_steps () const;
  template <typename append_next_step>
  void move (const append_next_step &func) const;
};

struct board_mask {
  struct board_map board;
  board_mask (const chessboard &chesses);
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
bool operator == (const point &l, const point &r);

#endif
