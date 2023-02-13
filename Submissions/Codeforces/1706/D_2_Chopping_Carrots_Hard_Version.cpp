#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;

void test_case() {
  vector<vector<int>> updates_at(N);

  int n, k;
  cin >> n >> k;
  // debug(n, k);

  vector<int> a(n);
  for (int &i : a) cin >> i;
  // debug(a);

  int mn_a = *min_element(a.begin(), a.end());

  auto nxt_div = [&](int num, int prv_div) {
    int nxt_p = num / (prv_div + 1);
    if (nxt_p == 0) return N - 2;
    int new_div = num / nxt_p;
    return new_div;
  };

  map<int, int> div_freq;
  vector<int> cur_entry(n);
  for (int i = 0; i < n; i++) {
    int low_div = a[i] / k;
    div_freq[low_div]++;
    int new_div = nxt_div(a[i], low_div);
    // debug(i, low_div, new_div);
    updates_at[low_div + 1].push_back(i);
    cur_entry[i] = low_div + 1;
  }
  // debug(div_freq);

  int ans = N;

  for (int mn = mn_a / k; mn <= mn_a; mn++) {
    // debug(mn);
    while (!updates_at[mn].empty()) {
      int i = updates_at[mn].back();
      updates_at[mn].pop_back();
      assert(mn != 0);
      int prv_div = mn - 1;
      int new_div = nxt_div(a[i], prv_div);
      // debug(i, prv_div, new_div);
      updates_at[new_div + 1].push_back(i);
      cur_entry[i] = new_div + 1;

      div_freq[prv_div]--;
      if (div_freq[prv_div] == 0) {
        div_freq.erase(prv_div);
      }
      div_freq[new_div]++;
    }

    // debug(div_freq);

    ans = min(ans, div_freq.rbegin()->first - div_freq.begin()->first);
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