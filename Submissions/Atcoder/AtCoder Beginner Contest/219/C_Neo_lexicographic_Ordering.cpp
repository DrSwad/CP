#include <bits/stdc++.h>
using namespace std;

string A;

string encode(string s) {
  string ss;
  for (char c : s) {
    ss += 'a' + find(A.begin(), A.end(), c) - A.begin();
  }
  return ss;
}

string decode(string s) {
  string ss;
  for (char c : s) {
    ss += A[c - 'a'];
  }
  return ss;
}

void test_case() {
  cin >> A;

  int n;
  cin >> n;

  vector<string> s(n);
  for (string &ss : s) cin >> ss, ss = encode(ss);

  sort(s.begin(), s.end());

  for (string ss : s) cout << decode(ss) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}