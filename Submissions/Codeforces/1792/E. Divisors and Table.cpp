#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m1, m2;
  cin >> n >> m1 >> m2;

  function<vector<int>(int)> prime_decompose = [&](int m) {
    vector<int> ret;
    for (int i = 2; i * i <= m; i++) {
      while (m % i == 0) {
        ret.push_back(i);
        m /= i;
      }
    }
    if (m > 1) ret.push_back(m);
    return ret;
  };

  vector<pair<int, int>> prime_freq;
  {
    vector<int> p1 = prime_decompose(m1);
    vector<int> p2 = prime_decompose(m2);
    vector<int> p3;
    merge(p1.begin(), p1.end(), p2.begin(), p2.end(), back_inserter(p3));
    for (int l = 0; l < p3.size(); ) {
      int r = l;
      while (r < p3.size() and p3[l] == p3[r]) r++;
      prime_freq.emplace_back(p3[l], r - l);
      l = r;
    }
  }

  vector<int> possible_cols{1};
  for (auto [p, f] : prime_freq) {
    int sz = possible_cols.size();
    for (ll e = 1, pp = p; e <= f; e++, pp *= p) {
      for (int i = 0; i < sz; i++) {
        ll d = pp * possible_cols[i];
        if (d <= n) {
          possible_cols.push_back(d);
        }
      }
    }
  }

  ll M = 1ll * m1 * m2;
  unordered_map<ll, bool> mult_vis;
  int ans_xor = 0;

  function<void(int, int, int)> go = [&](int col, int prime_index, int row) {
    if (prime_index >= prime_freq.size()) {
      mult_vis[1ll * row * col] = true;
      ans_xor ^= row;
      return;
    }

    auto [p, f] = prime_freq[prime_index];
    ll rem = M / col / row;
    for (ll e = 0, pp = 1; e <= f and rem % pp == 0; e++, pp *= p) {
      if (pp * row > col) break;
      int new_row = pp * row;
      if (mult_vis.find(1ll * col * new_row) != mult_vis.end()) break;
      go(col, prime_index + 1, new_row);
    }
  };
  
  sort(possible_cols.begin(), possible_cols.end(), greater<int>());
  for (int col : possible_cols) {
    go(col, 0, 1);
  }

  cout << mult_vis.size() << " " << ans_xor << "\n";
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
