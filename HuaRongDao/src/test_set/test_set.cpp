#include <iostream>
#include <set>
#include <string>

using namespace std;

struct mask {
  string str;
  bool operator < (const mask &r) const {
    return str < r.str;
  }
};

namespace std {
  template <>
  struct less<mask> {
    bool operator () (const mask &l, const mask &r) {
      return l.str < r.str;
    }
  };
}

bool operator < (const mask &l, const mask &r) {
  return l.str < r.str;
}

struct mask_less : public std::binary_function <mask, mask, bool> {
  bool operator () (const mask &l, const mask &r) const {
    return l.str < r.str;
  }
};

int main (int argc, char **argv) {
  set<mask, mask_less> masks;
  mask a; a.str = "hello";
  mask b;
  if (argc == 1)
    b.str = "hello";
  else
    b.str = argv[1];

  masks.insert (a);
  if (masks.find (b) == masks.end ())
    cout << "not found" << endl;
  else
    cout << "found" << endl;

  return 0;
}
