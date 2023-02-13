#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  vector<int> freq_a(10, 0), freq_b(10, 0);
  int ans = 0;
  while (!a.empty() or !b.empty()) {
    if (!a.empty() and (b.empty() or a.back() > b.back())) {
      if (a.back() < 10) freq_a[a.back()]++;
      else ans++, freq_a[to_string(a.back()).length()]++;
      a.pop_back();
    }
    else if (!b.empty() and (a.empty() or b.back() > a.back())) {
      if (b.back() < 10) freq_b[b.back()]++;
      else ans++, freq_b[to_string(b.back()).length()]++;
      b.pop_back();
    }
    else {
      if (a.back() < 10) {
        freq_a[a.back()]++;
        freq_b[b.back()]++;
      }
      a.pop_back(), b.pop_back();
    }
  }

  for (int i = 9; i > 1; i--) {
    int mn = min(freq_a[i], freq_b[i]);
    ans += max(freq_a[i] - mn, freq_b[i] - mn);
  }

  cout << ans << "\n";
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