#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> point;
#define x first
#define y second

point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y);
}

ll dot(const point &a, const point &b) {
  return 1ll * a.x * b.x + 1ll * a.y * b.y;
}

bool ortho(const point &o, const point &a, const point &b) {
  return dot(a - o, b - o) == 0;
}

ll dist2(const point &a, const point &b) {
  point d = a - b;
  return 1ll * d.x * d.x + 1ll * d.y * d.y;
}

bool is_rect(const vector<point> &p) {
  int n = 4;
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  do {
    bool flag = true;
    for (int i = 0; i < n; i++) {
      int prv = (i - 1 + n) % n;
      int nxt = (i + 1) % n;
      if (!ortho(p[order[i]], p[order[prv]], p[order[nxt]])) {
        flag = false;
        break;
      }
    }
    if (flag) return true;
  } while (next_permutation(order.begin(), order.end()));
  return false;
}

bool is_sq(const vector<point> &p) {
  int n = 4;
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  do {
    bool flag = true;
    for (int i = 0; i < n; i++) {
      int prv = (i - 1 + n) % n;
      int nxt = (i + 1) % n;
      if (!ortho(p[order[i]], p[order[prv]], p[order[nxt]]) or
          dist2(p[order[prv]], p[order[i]]) != dist2(p[order[i]], p[order[nxt]])
      ) {
        flag = false;
        break;
      }
    }
    if (flag) return true;
  } while (next_permutation(order.begin(), order.end()));
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 8;
  vector<point> p(n);
  for (auto &pp : p) cin >> pp.x >> pp.y;

  vector<int> sq, rect;
  for (int mask = 0; mask < 1 << n; mask++) {
    if (__builtin_popcount(mask) == 4) {
      vector<point> _sq, _rect;
      for (int i = 0; i < n; i++) {
        if (mask >> i & 1) _sq.push_back(p[i]);
        else _rect.push_back(p[i]);
      }
      if (is_sq(_sq) and is_rect(_rect)) {
        for (int i = 0; i < n; i++) {
          if (mask >> i & 1) sq.push_back(i);
          else rect.push_back(i);
        }
        break;
      }
    }
  }

  if (sq.empty() or rect.empty()) cout << "NO\n";
  else {
    cout << "YES\n";
    int n = 4;
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << sq[i] + 1;
    }
    cout << "\n";
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << rect[i] + 1;
    }
    cout << "\n";
  }

  return 0;
}