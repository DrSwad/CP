#include <bits/stdc++.h>
using namespace std;

int main() {
  const int TESTS = 30;
  const int DEPTH = 8;
  const string verdict_order[6] = {"WA", "TLE", "MLE", "RTE", "IDLE", "AC"};

  ifstream response_file;
  vector<vector<int>> results(TESTS);

  for (int d = 0; d < DEPTH; d++) {
    string file_name = string("out") + to_string(d) + string(".txt");
    response_file.open(file_name);

    for (int t = 0; t < TESTS; t++) {
      string response;
      getline(response_file, response);

      int result;
      if (response.find("Wrong answer") != string::npos) result = 0;
      else if (response.find("Time limit exceeded") != string::npos) result = 1;
      else if (response.find("Memory limit exceeded") != string::npos) result = 2;
      else if (response.find("Runtime error") != string::npos) result = 3;
      else if (response.find("Idleness limit exceeded") != string::npos) result = 4;
      else if (response.find("Accepted") != string::npos) result = 5;
      else assert(false);

      results[t].push_back(result);
    }

    response_file.close();
  }

  const int MAX_OPERATIONS = 1e6;
  vector<pair<int, int>> ranges(TESTS, make_pair(1, MAX_OPERATIONS));

  for (int t = 0; t < TESTS; t++) {
    for (int d = 0; d < DEPTH; d++) {
      auto &[L, R] = ranges[t];
      int segment = (R - L + 5) / 6;
      int i = results[t][d];
      int l = L + segment * i;
      int r = L + segment * (i + 1) - 1;
      L = l;
      R = r;
    }
    debug(t, ranges[t]);
  }

  return 0;
}
