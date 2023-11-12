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

  map<int, int> freq;
  for (int i = 0; i < n; i++) {
    int val = abs(need[i]);
    if (val == 0) continue;

    int small = 1;
    while (val % 2 == 0) small *= 2, val /= 2;
    int big = (val + 1) * small;

    // big is not a power of 2
    if (big != (big & -big)) {
      cout << "No\n";
      return;
    }

    if (need[i] < 0) swap(big, small);
    freq[big]++;
    freq[small]--;
  }

  for (auto [p2, cnt] : freq) {
    if (cnt != 0) {
      cout << "No\n";
      return;
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