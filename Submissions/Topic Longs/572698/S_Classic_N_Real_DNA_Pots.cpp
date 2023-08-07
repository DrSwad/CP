#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

int LIS(vector<int> a) {
  vector<int> v;
  for (int i : a) {
    auto it = upper_bound(v.begin(), v.end(), i);
    if (it == v.end()) v.push_back(i);
    else *it = i;
  }
  return v.size();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<point> p(n);
  for (auto & [x, y] : p) cin >> x >> y;

  function<bool(double)> check =
    [&](double slope) {
      vector<int> a(n);
      iota(a.begin(), a.end(), 0);
      sort(
        a.begin(),
        a.end(),
        [&](int i, int j) {
          if (i < j) return p[i].y + (p[j].x - p[i].x) * slope <= p[j].y;
          else return p[j].y + (p[i].x - p[j].x) * slope > p[i].y;
        }
      );
      return LIS(a) >= k;
    };

  double L = -1e9, R = 1e9;
  for (int t = 0; t < 100; t++) {
    double M = (L + R) / 2;
    if (check(M)) L = M;
    else R = M;
  }

  cout << fixed << setprecision(10) << L << "\n";

  return 0;
}