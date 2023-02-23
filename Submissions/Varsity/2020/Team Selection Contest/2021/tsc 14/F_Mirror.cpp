#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<double, double> pdd;
struct CHT { // Finds maximum
  private:
  vector<pdd> lines;

  public:
  CHT() {}
  void addLine(pdd line) { insert(line); }
  double query(double x) {
    if (lines.empty()) return HUGE_VAL;

    int L = 0, R = lines.size() - 1;
    while (L != R) {
      int mid1 = L + (R - L) / 3;
      int mid2 = R - (R - L) / 3;
      if (lines[mid1].x * x + lines[mid1].y
          >= lines[mid2].x * x + lines[mid2].y)
        R = mid2 - 1;
      else
        L = mid1 + 1;
    }
    return lines[L].x * x + lines[L].y;
  }

  private:
  bool bad(pdd line1, pdd line2, pdd line3) {
    return (line3.y - line1.y) * (line1.x - line2.x)
        <= (line2.y - line1.y) * (line1.x - line3.x);
  }
  void insert(pdd line) {
    while (lines.size() > 0 && lines.back().x == line.x)
      lines.pop_back();
    lines.push_back(line);
    int sz = lines.size();
    while (
        sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
      lines.erase(lines.end() - 2);
      sz--;
    }
  }
};

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, a;
    scanf("%d %d", &n, &a);

    vector<int> x(n), z(n);
    for (int i = 0; i < n; i++) { scanf("%d %d", &x[i], &z[i]); }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
      return z[i] != z[j] ? z[i] > z[j] : x[i] > x[j];
    });

    CHT mx[2], mn[2];
    for (int i : order)
      mx[0].addLine({1.0 / (a + z[i]), -(double)x[i] / (a + z[i])});
    for (int i : order) mx[1].addLine({1.0 / (a + z[i]), 0});
    reverse(order.begin(), order.end());
    for (int i : order)
      mn[0].addLine({-1.0 / (a + z[i]), (double)x[i] / (a + z[i])});
    for (int i : order) mn[1].addLine({-1.0 / (a + z[i]), 0});

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
      int v[2];
      for (int j = 0; j < 2; j++) { scanf("%d", &v[j]); }

      double ans = 1;
      for (int j = 0; j < 2; j++) {
        ans *= (-mx[j].query(v[j]) * a - mn[j].query(v[j]) * a);
      }

      printf("%.10lf\n", ans);
    }
  }

  return 0;
}