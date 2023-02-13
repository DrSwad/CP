#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> divs[N];

void init() {
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divs[j].push_back(i);
    }
  }
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  vector<int> r(n);
  {
    vector<int> nxt(m, n);
    map<int, int> nxt_freq;
    nxt_freq[n] = m;

    for (int i = n - 1; i >= 0; i--) {
      for (int d : divs[a[i]]) {
        if (d > m) break;
        nxt_freq[nxt[d - 1]]--;
        if (nxt_freq[nxt[d - 1]] == 0) {
          nxt_freq.erase(nxt[d - 1]);
        }
        nxt[d - 1] = i;
        nxt_freq[nxt[d - 1]]++;
      }

      r[i] = nxt_freq.rbegin()->first;
    }
  }

  int ans = -1;
  for (int i = 0; i < n; i++) {
    if (r[i] < n) {
      int cur = a[r[i]] - a[i];
      ans = ans == -1 ? cur : min(ans, cur);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}