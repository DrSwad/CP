#include <bits/stdc++.h>
using namespace std;

void answer(bool ans) {
  cout << (ans ? "YES" : "NO") << "\n";
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector grid(n, vector(m, 0));
  for (auto &row : grid) {
    for (int &i : row) cin >> i, i--;
  }

  if (m == 1) answer(true);

  vector<int> sorted_perm(m);
  iota(sorted_perm.begin(), sorted_perm.end(), 0);

  set<vector<int>> st;
  {
    st.insert(sorted_perm);
    for (int i = 0; i < m; i++) {
      for (int j = i + 1; j < m; j++) {
        swap(sorted_perm[i], sorted_perm[j]);
        st.insert(sorted_perm);
        swap(sorted_perm[i], sorted_perm[j]);
      }
    }
  }

  for (int row = 0; row < n; row++) {
    set<vector<int>> nst;
    vector<int> &cur_perm = grid[row];
    if (st.find(cur_perm) != st.end()) nst.insert(cur_perm);
    for (int i = 0; i < m; i++) {
      for (int j = i + 1; j < m; j++) {
        swap(cur_perm[i], cur_perm[j]);
        if (st.find(cur_perm) != st.end()) nst.insert(cur_perm);
        swap(cur_perm[i], cur_perm[j]);
      }
    }
    swap(st, nst);
  }

  answer(!st.empty());

  return 0;
}