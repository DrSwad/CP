#include <bits/stdc++.h>
using namespace std;

void answer(bool ans, int val = -1) {
  if (ans) cout << "unique\n" << val << "\n";
  else cout << "not unique\n";
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n == 1) answer(false);

  int diff = a[0], period = 1;
  for (int i = 0; i < n; i++, period++) {
    if (i > 0 and a[i] > a[i - 1] + diff) break;
  }

  if (period > n) answer(false);

  int last;
  for (int i = 1; i < n; i++) {
    if (a[i] > a[i - 1] + diff) last = i;
  }

  int rem = (n - 1) - last;
  debug(diff, period, last, rem);
  if (rem == period - 2) answer(false);
  else if (rem == period - 1) answer(true, a.back() + diff + 1);
  else answer(true, a.back() + diff);

  return 0;
}