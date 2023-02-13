#include <bits/stdc++.h>
using namespace std;

void answer(long long ans) {
  cout << ans << "\n";
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (a[0] != 0) answer(-1);

  long long ans = 0;
  int curr = 0;
  for (int i = n - 1; i >= 0; i--, curr--) {
    if (a[i] < curr) answer(-1);
    if (a[i] == curr) continue;
    curr = a[i];
    ans += curr;
  }

  if (curr != -1) answer(-1);
  answer(ans);

  return 0;
}