#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<int> mapped_to(26);
  iota(mapped_to.begin(), mapped_to.end(), 0);

  for (int i = 0; i < n; i++) {
    int at = s[i] - 'a';
    int to = mapped_to[at];
    while (to > 0 and k > 0) {
      to = mapped_to[to - 1];
      for (int j = at; j > to; j--) {
        mapped_to[j] = to;
      }
      k--;
    }

    s[i] = 'a' + to;
  }

  cout << s << "\n";
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