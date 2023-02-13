#include <bits/stdc++.h>
using namespace std;

const int N = 2000 + 3;
const int MAX_TABLES = N * N / 2;

int at_most_one_triple_per_table(int n, int r, vector<int> a) {
  int cnt2 = 0, cnt3 = 0;
  for (int &i : a) {
    if (i % 2 == 0) cnt2 += i / 2;
    else cnt2 += (i - 3) / 2, cnt3++, i -= 3;
  }

  function<int(int, int)> consider = [&](int cnt2, int cnt3) {
    int with3 = (r - 3) / 2;
    int rem2 = cnt2 - cnt3 * with3;
    if (rem2 <= 0) return cnt3;

    int without3 = r / 2;
    return cnt3 + (rem2 + (without3 - 1)) / without3;
  };

  int ans = consider(cnt2, cnt3);

  for (int i = 0; i < n; i++) {
    while (a[i] >= 6) {
      a[i] -= 6;
      cnt2 -= 3;
      cnt3 += 2;
      ans = min(ans, consider(cnt2, cnt3));
    }
  }

  return ans;
}

int at_most_one_triple_per_group(int n, int r, vector<int> a) {
  int cnt2 = 0, cnt3 = 0;
  for (int i : a) {
    if (i % 2 == 0) cnt2 += i / 2;
    else cnt2 += (i - 3) / 2, cnt3++;
  }

  function<bool(int)> check = [&](int tables) {
    vector<int> capacity(tables, r);
    int rem2 = cnt2, rem3 = cnt3;

    if (r % 2 == 1) {
      for (int i = 0; i < tables; i++) {
        if (rem3 == 0) break;
        capacity[i] -= 3;
        rem3--;
      }
    }

    for (int i = 0; i < tables; i++) {
      int max6 = capacity[i] / 6;
      int take6 = min(rem3 / 2, max6);
      rem3 -= take6 * 2;
      capacity[i] -= 6 * take6;

      int max2 = capacity[i] / 2;
      int take2 = min(rem2, max2);
      rem2 -= take2;
      capacity[i] -= 2 * take2;

      int max3 = capacity[i] / 3;
      int take3 = min(rem3, max3);
      rem3 -= take3;
      capacity[i] -= 3 * take3;
    }

    return rem2 == 0 and rem3 == 0;
  };

  int L = 1, R = MAX_TABLES;
  while (L != R) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid + 1;
  }

  return L;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, r;
  cin >> n >> r;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (r % 2 == 0) {
    cout << at_most_one_triple_per_group(n, r, a) << "\n";
  }
  else {
    cout << min(at_most_one_triple_per_group(n, r, a), at_most_one_triple_per_table(n, r, a)) << "\n";
  }

  return 0;
}