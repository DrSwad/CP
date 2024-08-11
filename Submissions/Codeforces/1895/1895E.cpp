#include <bits/stdc++.h>
using namespace std;

template<typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>&a, const F&f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};

void test_case() {
  int n[2];
  vector<vector<pair<int, int>>> cards(2);
  SparseTable<int> *mx[2];

  for (int player = 0; player < 2; player++) {
    cin >> n[player];
    cards[player].resize(n[player]);
    for (int i = 0; i < n[player]; i++) {
      cin >> cards[player][i].first;
    }
    for (int i = 0; i < n[player]; i++) {
      cin >> cards[player][i].second;
    }

    sort(cards[player].begin(), cards[player].end());

    vector<int> ids(n[player]);
    iota(ids.begin(), ids.end(), 0);
    mx[player] = new SparseTable(
      ids,
      (function<int(const int&, const int&)>)[&cards, player](int i, int j) {
      if (i == -1) return j;
      if (j == -1) return i;
      if (cards[player][i].second >= cards[player][j].second) return i;
      else return j;
    }
    );
  }

  vector<int> order(n[0]);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      return cards[0][i].second < cards[0][j].second;
    }
  );

  function<int(int, int)> play =
    [&](int player, int card) {
      vector vis(2, vector<bool>());
      for (int player = 0; player < 2; player++) {
        vis[player].resize(n[player], false);
      }

      while (true) {
        if (vis[player][card]) return 0;
        vis[player][card] = true;

        auto it = upper_bound(cards[player ^ 1].begin(), cards[player ^ 1].end(), make_pair(cards[player][card].second + 1, 0));
        if (it == cards[player ^ 1].end()) return player == 0 ? 1 : -1;

        int index = it - cards[player ^ 1].begin();
        card = mx[player ^ 1]->get(index, n[player ^ 1] - 1);
        player = player ^ 1;
      }
    };

  int L = -1, R = n[0];
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (play(0, order[mid]) == 1) R = mid;
    else L = mid;
  }
  int winning_from = R;

  L = -1, R = winning_from;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (play(0, order[mid]) == 0) R = mid;
    else L = mid;
  }
  int drawing_from = R;

  int losing_from = 0;

  cout << (n[0] - winning_from) << " " << (winning_from - drawing_from) << " " << (drawing_from - losing_from) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}