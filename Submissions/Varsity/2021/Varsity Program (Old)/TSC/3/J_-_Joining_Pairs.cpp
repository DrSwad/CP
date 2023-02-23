#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int X, Y;
  cin >> X >> Y;

  int n;
  cin >> n;

  vector<tuple<int, int, int>> v;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if ((x1 == 0 or x1 == X or y1 == 0 or y1 == Y) and
        (x2 == 0 or x2 == X or y2 == 0 or y2 == Y)
        ) {
      v.push_back({i, x1, y1});
      v.push_back({i, x2, y2});
    }
  }

  auto dist = [&](int x, int y) {
    if (x == 0) return (long long)y;
    if (y == Y) return (long long)X + x;
    if (x == X) return (long long)X + Y + (Y - y);
    return (long long)X + Y + X + (X - x);
  };

  sort(
    v.begin(),
    v.end(),
    [&](const auto &i, const auto &j) {
    auto [id1, x1, y1] = i;
    auto [id2, x2, y2] = j;
    return dist(x1, y1) < dist(x2, y2);
  }
    );

  stack<int> st;
  for (auto [id, x, y] : v) {
    if (!st.empty() and st.top() == id) {
      st.pop();
    }
    else {
      st.push(id);
    }
  }

  cout << (st.empty() ? 'Y' : 'N') << "\n";

  return 0;
}