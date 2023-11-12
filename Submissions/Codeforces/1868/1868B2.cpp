#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll sum = 0;
  for (int i : a) sum += i;

  if (sum % n != 0) {
    cout << "No\n";
    return;
  }

  int avg = sum / n;

  vector<int> need(n);
  for (int i = 0; i < n; i++) {
    need[i] = avg - a[i];
  }

  map<int, array<int, 3>> freq;
  for (int i = 0; i < n; i++) {
    int val = abs(need[i]);
    if (val == 0) continue;

    // if val is a power of 2
    if (val == (val & -val)) {
      if (need[i] > 0) freq[__builtin_ctz(val)][2]++;
      else freq[__builtin_ctz(val)][1]++;
    }
    else {
      int small = 1;
      while (val % 2 == 0) small *= 2, val /= 2;
      int big = (val + 1) * small;

      // big is not a power of 2
      if (big != (big & -big)) {
        cout << "No\n";
        return;
      }

      if (need[i] < 0) swap(big, small);
      freq[__builtin_ctz(big)][0]++;
      freq[__builtin_ctz(small)][0]--;
    }
  }

  while (!freq.empty()) {
    auto [p2, cnt] = *freq.begin();
    freq.erase(freq.begin());

    auto [cnt_fixed, cnt_neg, cnt_pos] = cnt;
    int tot = cnt_fixed - cnt_neg + cnt_pos;

    if (tot % 2 == 1) {
      cout << "No\n";
      return;
    }

    if (tot > 0) {
      if (tot / 2 > cnt_pos) {
        cout << "No\n";
        return;
      }
      if (tot / 2) freq[p2 + 1][0] += tot / 2;
    }
    else {
      tot = -tot;
      if (tot / 2 > cnt_neg) {
        cout << "No\n";
        return;
      }
      if (tot / 2) freq[p2 + 1][0] -= tot / 2;
    }
  }

  cout << "Yes\n";
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