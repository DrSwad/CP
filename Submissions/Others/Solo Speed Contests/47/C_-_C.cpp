#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> freq(N + 1, 0);
  while (n--) {
    int a;
    cin >> a;
    freq[a] = 1;
  }

  string ans;

  for (int l = 1, r; l <= N; l = r) {
    if (!freq[l]) {
      r = l + 1;
      continue;
    }

    r = l;
    while (r <= N and freq[r]) r++;

    if (!ans.empty()) ans += ' ';
    ans += to_string(l);
    if (r - l == 2) ans += ' ' + to_string(r - 1);
    if (r - l > 2) ans += '-' + to_string(r - 1);
  }

  cout << ans << "\n";

  return 0;
}