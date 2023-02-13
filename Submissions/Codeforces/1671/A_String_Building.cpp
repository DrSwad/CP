#include <bits/stdc++.h>
using namespace std;

void answer(bool ans) {
  cout << (ans ? "YES" : "NO") << "\n";
}

void test_case() {
  string s;
  cin >> s;

  if (s.length() < 2) return answer(false);
  else if (s[0] != s[1]) return answer(false);
  else if (s[s.length() - 1] != s[s.length() - 2]) return answer(false);
  else if (s.find("aba") != string::npos) return answer(false);
  else if (s.find("bab") != string::npos) return answer(false);
  else return answer(true);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}