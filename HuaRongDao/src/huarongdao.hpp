#ifndef HUARONGDAO_HPP 
#define HUARONGDAO_HPP

#include <deque>
#include <list>
#include <memory>
#include <string>

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
    for (int r = 0; r < max_row; ++r)
      for (int c = 0; c < max_col; ++c)
        board_[r][c] = 0;
  }
};

enum chess_type {
  cao_cao, guan_yu, zhang_fei, zhao_yun, ma_chao, huang_zhong, zu
};

struct chess_id {
  chess_type type;
  int width;
  int height;
  int key;
  std::string info;
};

struct chess_id get_chess (chess_type type);

class chess {
public:
  chess (chess_type type, point p)
    : pos_ (p)
    { id_ = get_chess (type); }
public:
  std::string to_mask () const;
  virtual int key () const { return id_.key; }
  void fill_board (board_map &board) const;
//  void to_right (board_map &input, 
//                 board_map &output);
//  void to_left (chessboard &board) = 0;
//  void to_up (chessboard &board) = 0;
//  void to_down (chessboard &board) = 0;
public:
  point pos_;
  chess_id id_;
};

//enum direction {
//  up, down, right, left
//};


class chessboard {
public:
  std::deque<chess> chesses;
  struct board_map board_;
  void push_chess (chess &c);
  bool is_solved () const;
  void show () const;
  std::deque<chessboard> can_move_steps () const;
};

struct board_mask {
  std::string mask;
  board_mask (chessboard &chesses);
  std::string get_mask () const { return mask; }
};

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

//class cao_cao : public chess {
//public:
//  cao_cao (point &p)
//    { pos_ = p; width_ = 2; height_ = 2; }
//  int key () const { return 1;}
//};
//
//class guan_yu : public chess {
//public:
//  guan_yu (const point &p)
//    { pos_ = p; width_ = 2; height_ = 1; }
//  int key () const { return 10;}
//};
//
//class zhang_fei : public chess {
//public:
//  zhang_fei (const point &p)
//    { pos_ = p; width_ = 1; height_ = 2; }
//  int key () const { return 11;}
//};
//
//class zhao_yun : public chess {
//public:
//  zhao_yun (const point &p)
//    { pos_ = p; width_ = 1; height_ = 2; }
//  int key () const { return 12;}
//};
//
//class ma_chao : public chess {
//public:
//  ma_chao (const point &p)
//    { pos_ = p; width_ = 1; height_ = 2; }
//  int key () const { return 13;}
//};
//
//class huang_zhong : public chess {
//public:
//  huang_zhong (const point &p)
//    { pos_ = p; width_ = 1; height_ = 2; }
//  int key () const { return 14;}
//};
//
//class zu : public chess {
//public:
//  zu (const point &p)
//    { pos_ = p; width_ = 1; height_ = 1; }
//  int key () const { return 20;}
//};

#endif
