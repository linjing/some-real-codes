#ifndef HUARONGDAO_HPP 
#define HUARONGDAO_HPP

class chessboard;
class chess;

class chess {
public:
  virtual void to_right (chessboard &board) = 0;
  virtual void to_left (chessboard &board) = 0;
  virtual void to_up (chessboard &board) = 0;
  virtual void to_down (chessboard &board) = 0;
protected:
  int x_;
  int y_;
  int width_;
  int height_;
};

enum direction {
  up, down, right, left
};

class chessboard {
public:
  virtual void move (chess &c, const direction &d) = 0;
};

#endif
