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
//  vector<vector<char> > output_s;
};

Case_Data get_case_data() {
  Case_Data cd;
  scanf("%d", &cd.N);
  cerr << "input N: " << cd.N << endl;

  cd.input.resize(cd.N+1);
  for(int i = 0; i < cd.N - 1; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    cd.input[a].push_back(b);
    cd.input[b].push_back(a);
  }
  for (int i = 1; i <= cd.N; ++i) {
    cerr << "input " << i << ": ";
    for (int j = 0; j < cd.input[i].size (); ++j) {
      cerr << cd.input[i][j] << " ";
    }
    cerr << endl;
  }
  return cd;
}

void deal(Case_Data &cd) {
  // try each node as root of the tree
  int max_weight = 0;
  for (int root = 1; root <= cd.N; ++root) {
    set<int> used;
    used.insert(root);
    deque<int> keep;
    keep.push_back(root);

    map<int, vector<int> > tree;
    vector<pair<int, int> > lines_c_p;

    cerr << "root is " << root << ". ";
    while(true) {
      if(keep.size() == 0) {
        cerr << endl;
        break;
      }
      int cur = keep.front(); keep.pop_front();
      for(int i = 0; i<cd.input[cur].size(); ++i) {
        int n = cd.input[cur][i];
        if (used.find(n) == used.end()) {
          cerr << "P" << cur << "C" << n << " ";
          keep.push_back(n);
          used.insert(n);
          tree[cur].push_back(n);
          lines_c_p.push_back(make_pair(n, cur));
        }
      }
    }
    cerr << "show tree" << endl;
    map<int, int> node_weight;
    int cur_p = 0;
    for(int i = lines_c_p.size () - 1; i >=0; --i) {
      if (node_weight[lines_c_p[i].first] == 0) {
        node_weight[lines_c_p[i].first] = 1;
        cerr << "weight " << lines_c_p[i].first << " " << 1<< endl;
        max_weight = std::max(max_weight, 1);
      }
      if ((cur_p != lines_c_p[i].second && cur_p != 0)
          || (i == 0 && cur_p != 0)) {
        vector<int> weights;
        for (int c = 0; c < tree[cur_p].size (); ++c) {
          weights.push_back(node_weight[tree[cur_p][c]]);
        }
        if (weights.size () == 0)
          assert(false); // parent always has children
        else if (weights.size () == 1)
          node_weight[cur_p] = 1; // remove the only child
        else {
          sort(weights.begin(), weights.end(), std::greater<int>());
          node_weight[cur_p] = weights[0] + weights[1] + 1;
          cerr << "weight " << cur_p << " " << weights[0] + weights[1] + 1 << endl;
          max_weight = std::max(node_weight[cur_p], max_weight);
        }
      }
      cur_p = lines_c_p[i].second;
    }

  }
  cout << "Case #" << cd.i << ": " << (cd.N - max_weight) << endl;
}
int main(int argc, char **argv) {
  int case_number; char skip;
  scanf ("%d%c", &case_number, &skip);
  cerr << "input case_number " << case_number << endl;
  for (int i = 1; i <= case_number; ++i) {
    Case_Data cd = get_case_data();
    cd.i = i;
    deal(cd);
  }
}
