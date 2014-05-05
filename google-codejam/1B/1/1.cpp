#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <string.h>
#include <set>
#include <deque>
#include <map>
#include <cassert>
using namespace std;

struct Case_Data {
  int i;
  int N;
  vector<vector<int> > input;
  char input2[101][101];
  char chs[101];
  int num[101][101];
  int n;
//  vector<vector<char> > output_s;
};

Case_Data get_case_data() {
  Case_Data cd;
  scanf("%d", &cd.N);
  cerr << "input N: " << cd.N << endl;

  cd.input.resize(cd.N+1);
  for(int i = 0; i < cd.N; ++i) {
    scanf("%s", &cd.input2[i][0]);
    cerr << i << " " << cd.input2[i] << endl;
  }
  return cd;
}

int deal(Case_Data &cd) {
  int n = strlen(cd.input2[0]);
  cerr << n << endl;
  if(1) {
    int l = 0;
    int n = strlen(cd.input2[l]);
    char last = cd.input2[l][0];
    int total = 1;
    int idx = 0;
    for (int i = 1; i < n; ++i) {
      if (cd.input2[l][i] == last) {
        total += 1;
      } else {
        cd.chs[idx] = last;
        cd.num[0][idx] = total;
        cerr << last << total;
        last = cd.input2[l][i];
        total = 1;
        idx ++;
      }
    }
    cd.chs[idx] = last;
    cd.num[l][idx] = total;
    cd.n = idx;
    cerr << last << total;
  }
  cerr << endl;

  for (int l = 1; l < cd.N; ++l) {
//    for (int idx = 0; idx < cd.n; ++ idx) {
      int cnt = 0;  int idx = 0;
      char cur = cd.chs[idx];
      for(int i = 0; cd.input2[l][i] != '\0'; ++i) {
        if (cd.input2[l][i] == cur) {
          cnt ++;
        } else {
          if (cnt == 0) {
            return -1;
          } else {
            cd.num[l][idx] = cnt;
            cerr << cur << cnt;
            cnt = 1;
            idx ++;
            cur = cd.chs[idx];
            if (cd.input2[l][i] != cur)
              return -1;
          }
        }
      }
      cd.num[l][idx] = cnt;
      cerr << cur << cnt;
      //cerr << "parse " << idx << "xxxx" << cd.n << endl;
      if (idx != cd.n)
        return -1;
      cerr << endl;
  }

  int total = 0;
  for (int idx = 0; idx <= cd.n; ++idx) {
    int num[101];
    for(int i = 0; i < cd.N; ++i) {
      num[i] = cd.num[i][idx];
    }
    sort(&num[0], &num[cd.N]);
    int t1 = 0;
    int mid = num[cd.N/2];
    for (int i = 0; i < cd.N; ++i) {
      t1 += abs(mid - cd.num[i][idx]);
    }
    cerr << "t1 " << t1 << endl;
    total += t1;
  }
  return total;
}
int main(int argc, char **argv) {
  int case_number; char skip;
  scanf ("%d%c", &case_number, &skip);
  cerr << "input case_number " << case_number << endl;
  for (int i = 1; i <= case_number; ++i) {
    Case_Data cd = get_case_data();
    cd.i = i;
    int ret = deal(cd);
    if (ret < 0)
      cout << "Case #" << cd.i << ": " << "Fegla Won" << endl;
    else 
      cout << "Case #" << cd.i << ": " << ret << endl;
  }
}
