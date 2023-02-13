#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case(int n, int m) {
  int len[2] = {n, m};
  multiset<ll> st[2];
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < len[it]; i++) {
      ll v;
      cin >> v;
      st[it].insert(v);
    }
  }

  int winner = -1;

  while (winner == -1) {
    for (int player = 0; player < 2; player++) {
      if (st[player].empty()) {
        winner = player ^ 1;
        break;
      }
      if (st[player].size() > 1 and (*st[player].rbegin()) <= (*st[player ^ 1].rbegin())) {
        int sum = 0;
        for (int it = 0; it < 2; it++) {
          sum += *prev(st[player].end());
          st[player].erase(prev(st[player].end()));
        }
        st[player].insert(sum);
      }
      else {
        auto it = upper_bound(st[player ^ 1].begin(), st[player ^ 1].end(), *st[player].rbegin());
        if (it == st[player ^ 1].begin()) {
          winner = player ^ 1;
          break;
        }
        it--;
        st[player ^ 1].erase(it);
      }
    }
  }

  cout << (winner ? "Buyout Limited" : "Takeover Incorporated") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  for (int cs = 1; cin >> n >> m; cs++) {
    cout << "Case " << cs << ": ";
    test_case(n, m);
  }

  return 0;
}