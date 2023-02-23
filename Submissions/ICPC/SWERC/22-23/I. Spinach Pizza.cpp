#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos(-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
};
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
double area_of_triangle(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) * 0.5);
}

int main() {
  int n;
  cin >> n;

  vector<PT> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
  }

  vector<bool> vis(n, true);
  int rem = n;

  if (n % 2 == 0) cout << "Alberto" << endl;
  else {
    cout << "Beatrice" << endl;
    int v;
    cin >> v;
    v--;
    vis[v] = false;
    rem--;
  }

  while (rem >= 3) {
    vector<int> rems;
    for (int i = 0; i < n; i++) {
      if (vis[i]) rems.push_back(i);
    }

    assert(rems.size() == rem);
    double min_area, min_i = -1;
    for (int i = 0; i < rem; i++) {
      int pi = (i - 1 + rem) % rem;
      int ni = (i + 1) % rem;
      double cur_area = area_of_triangle(p[rems[pi]], p[rems[i]], p[rems[ni]]);
      if (min_i == -1 or cur_area < min_area) {
        min_i = i;
        min_area = cur_area;
      }
    }

    cout << rems[min_i] + 1 << endl;
    vis[rems[min_i]] = false;
    rem--;

    if (rem >= 3) {
      int v;
      cin >> v;
      v--;
      vis[v] = false;
      rem--;
    }
  }

  return 0;
}
