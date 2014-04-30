#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;


struct Case_Data {
  int i;
  int N; int L;
  vector<vector<char> > input_s;
  vector<vector<char> > output_s;
};

int is_the_same(vector<vector<char> > &input_s, vector<vector<char> >&output_s) {
//  sort(input_s.begin(), input_s.end());
  sort(output_s.begin(), output_s.end());
  for(int i = 0; i < input_s.size(); ++i){
    if (strncmp(&input_s[i][0], &output_s[i][0], input_s[i].size()) != 0)
      return 1;
  }
  return 0;
}
void deal(Case_Data &cd) {
  sort(cd.input_s.begin(), cd.input_s.end());
  int min_flip = cd.L + 1;
  for(int kk = 0; kk < cd.N; ++kk) {
    int flip_times = 0;
    vector<char> acts(cd.L);
    for(int p = 0; p < cd.L; ++p) {
      if(cd.input_s[0][p] == cd.output_s[kk][p]) {
        acts[p] = 'K';
      } else {
        acts[p] = 'F'; flip_times ++;
      }
    }
//    cout << "Case #" << cd.i << " " << flip_times << ": ";
//    for (int p = 0; p < cd.L; ++p)
//      cout << acts[p];
//    cout << endl;

    vector<vector<char> > fliped_output;
    fliped_output.resize(cd.N);
    for(int i = 0; i < cd.N; ++i) {
      fliped_output[i].resize(cd.L+1);
      for(int p = 0; p < cd.L; ++p) {
        if (acts[p] == 'K') fliped_output[i][p] = cd.output_s[i][p];
        else fliped_output[i][p] = '0' + '1' - cd.output_s[i][p];
      }
      fliped_output[i][cd.L] = '\0';
    }
    if (is_the_same(cd.input_s, fliped_output) == 0) {
      min_flip = std::min(flip_times, min_flip);
      cerr << "the same" << endl;
    }
  }
  if (min_flip > cd.L)
    cout << "Case #" << cd.i << ": NOT POSSIBLE" << endl;
  else
    cout << "Case #" << cd.i << ": " << min_flip << endl;
}
Case_Data get_case_data() {
  int N, L; char skip;
  cin >> N >> L;
  cerr << "xx" << N << " " << L << endl;
  vector<int> input(N);
  vector<vector<char> > input_s(N);
  vector<vector<char> > output_s(N);
  vector<int> output(N);
  vector<char> temp(L+1);
  for(int i = 0; i < N; ++i) {
    input_s[i].resize(L+1);
    scanf("%s%c", &input_s[i][0], &skip);
    input_s[i][L] = '\0';
//    cerr << string(&input_s[i][0], &input_s[i][L]) << endl;
  }
  for(int i = 0; i < N; ++i) {
    output_s[i].resize(L+1);
    scanf("%s%c", &output_s[i][0], &skip);
    output_s[i][L] = '\0';
  }
  //for(int i = 0; i < N; ++i)
  //  cerr << input_s[i].size () << " " << input_s[i][0] << "  " << string(&input_s[i][0],&input_s[i][L]) << endl;
  //cerr << endl;
  //for(int i = 0; i < N; ++i)
  //  cerr << string(&output_s[i][0],&output_s[i][L]) << " ";
  //cerr << endl;

  Case_Data cd;
  cd.N = N; cd.L = L;
  cd.input_s = input_s;
  cd.output_s = output_s;
  return cd;
}

int main(int argc, char **argv) {
  int case_number; char skip;
  scanf ("%d%c", &case_number, &skip);
  cerr << "case_number " << case_number << endl;
  for (int i = 1; i <= case_number; ++i) {
    Case_Data cd = get_case_data();
    cd.i = i;
    deal(cd);
  }
}
