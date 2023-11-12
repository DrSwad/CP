#include <bits/stdc++.h>
using namespace std;

void test_case(vector<string> v) {
  int max_len = 0;
  for (auto &s : v) {
    reverse(s.begin(), s.end());
    max_len = max(max_len, (int)s.length());
  }

  sort(v.begin(), v.end());
  for (auto s : v) {
    reverse(s.begin(), s.end());
    cout << string(max_len - s.length(), ' ') << s << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> v;
  string line;
  int cs = 0;

  while (getline(cin, line)) {
    if (line.empty()) {
      if (cs++) cout << "\n";
      test_case(v);
      v.clear();
    }
    else {
      v.push_back(line);
    }
  }

  if (cs++) cout << "\n";
  if (!v.empty()) test_case(v);

  return 0;
}