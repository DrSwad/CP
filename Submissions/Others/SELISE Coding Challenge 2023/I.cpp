#include <bits/stdc++.h>
using namespace std;

bool solve(string s, string p) {
  map<char, int> freq_s, freq_p;

  for (char c : s) freq_s[c]++;
  for (char c : p) freq_p[c]++;
  for (char c : p) if (freq_s[c] < freq_p[c]) return false;

  return true;
}

void test_case() {
  string s;
  while (s.empty()) getline(cin, s);

  string p1 = "SELISE";
  string p2 = "SELISE Digital Platforms";

  bool ans1 = solve(s, p1);
  bool ans2 = solve(s, p2);

  if (ans2) assert(ans1);

  if (ans1 and ans2) cout << "BOTH\n";
  else if (ans1) cout << p1 << "\n";
  else if (ans2) cout << p2 << "\n";
  else cout << "NONE\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
