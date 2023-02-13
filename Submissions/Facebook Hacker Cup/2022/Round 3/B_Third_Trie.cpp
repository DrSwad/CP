#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int C = 26;

void test_case() {
  int n;
  cin >> n;

  vector<int> sz(n);
  vector<vector<vector<int>>> trie(n);

  for (int i = 0; i < n; i++) {
    cin >> sz[i];
    trie[i].resize(sz[i], vector<int>(C, -1));
    for (int j = 1; j < sz[i]; j++) {
      int p;
      char c;
      cin >> p >> c;
      trie[i][p - 1][c - 'a'] = j;
    }
  }

  vector<vector<int>> merged_trie(1, vector<int>(C, -1));
  vector<int> sub(1, 0);
  // debug(merged_trie.size());
  {
    int depth = 0;
    stack<vector<pair<int, int>>> stk;
    function<void(int)> go = [&](int at) {
      const vector<pair<int, int>> &pos = stk.top();
      depth++;
      // debug(at, depth, merged_trie.size());
      sub[at] = pos.size();
      for (int c = 0; c < C; c++) {
        vector<pair<int, int>> npos;
        for (auto [i, p] : pos) {
          if (trie[i][p][c] != -1) {
            npos.push_back(make_pair(i, trie[i][p][c]));
          }
        }
        if (!npos.empty()) {
          int id = (int)merged_trie.size();
          merged_trie.push_back(vector<int>(C, -1));
          sub.push_back(0);
          merged_trie[at][c] = id;
          stk.push(npos);
          go(merged_trie[at][c]);
        }
      }
      depth--;
    };
    vector<pair<int, int>> pos(n);
    for (int i = 0; i < n; i++) pos[i] = make_pair(i, 0);
    stk.push(pos);
    go(0);
  }

  ll ans = 0;
  for (int sz : sub) {
    int rem = n - sz;
    ans += n * (n - 1) * (n - 2) / 6 - rem * (rem - 1) * (rem - 2) / 6;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}