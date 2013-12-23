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
struct board_map;

struct point {
  point () : pos (0) {}
  point (uint8_t r, uint8_t c) { pos = (r << 4) + c; }
  inline uint8_t row () const { return pos >> 4;}
  inline uint8_t col () const { return pos & 15;}
  inline void down () { pos -= 16;}
  inline void up () {pos += 16;}
  inline void left () {pos -= 1;}
  inline void right () {pos += 1;}
  inline bool operator == (const point &r) const {
    return pos == r.pos;
  }
  inline uint8_t get () const { return pos; }

private:
  uint8_t pos; // rrrrcccc
};

enum chess_type {
  cao_cao = 1, guan_yu = 2, zhang_fei = 3, zhao_yun = 3, ma_chao = 3,
  huang_zhong = 3, w1_h2 = 3, zu = 4
};

uint8_t chess_height (const chess_type &type);
uint8_t chess_width (const chess_type &type);

class chess {
public:
  chess (const chess_type &type, const point &p)
    : pos_ (p), type_ (type) {}
public:
  std::string to_mask () const;
  void fill_board (board_map &board) const;
public:
  inline uint8_t key () const { return (uint8_t) type_; }
  inline uint8_t width () const { return chess_width (type_); }
  inline uint8_t height () const { return chess_height (type_); }
public:
  point pos_;
private:
  chess_type type_;
};

//enum direction {
//  up, down, right, left
//};

struct board_map {
  uint8_t board[board_size];
  board_map () { memset (&board, 0, board_size * sizeof (uint8_t)); }
  std::string get_mask () const;
  size_t get_hash () const;
};

class chessboard {
public:
  std::vector<chess> chesses;
  struct board_map board_;
  int steps;
public:
  void push_chess (chess &c);
  bool is_solved () const;
  void show () const;
  template <typename append_next_step>
  void move (const append_next_step &func) const;
};

namespace std {
  template <>
  struct hash<board_map> {
    size_t operator () (const board_map&m) const {
      return m.get_hash ();
    }
  };
}

struct board_map_less {
  bool operator () (const board_map &l, const board_map &r) {
    return l.get_mask () < r.get_mask ();
  }
};

bool operator == (const board_map &l, const board_map &r);
bool operator < (const board_map &l, const board_map &r);

#endif
