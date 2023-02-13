#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define x first
#define y second
typedef pair<ll, ll> pll;

struct CHT {
private:
  vector<pll> lines;
public:
  CHT() {}
  void addLine(pll line) {
    insert(line);
  }
  ll query(ll x) {
    if (lines.empty()) return LLONG_MIN;

    int L = 0, R = lines.size() - 1;
    while (L != R) {
      int mid1 = L + (R - L) / 3;
      int mid2 = R - (R - L) / 3;
      if (lines[mid1].x * 1LL * x + lines[mid1].y
          >= lines[mid2].x * 1LL * x + lines[mid2].y) R = mid2 - 1;
      else L = mid1 + 1;
    }
    return lines[L].x * 1LL * x + lines[L].y;
  }
private:
  bool bad(pll line1, pll line2, pll line3) {
    return (line3.y - line1.y) * 1LL * (line1.x - line2.x)
           <= (line2.y - line1.y) * 1LL * (line1.x - line3.x);
  }
  void insert(pll line) {
    while (lines.size() > 0 && lines.back().x == line.x) lines.pop_back();
    lines.push_back(line);
    int sz = lines.size();
    while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
      lines.erase(lines.end() - 2);
      sz--;
    }
  }
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<ll> a(n);
  vector<ll> b(m), k(m);

  for (ll &i : a) scanf("%lld", &i);
  for (int i = 0; i < m; i++) {
    scanf("%lld %lld", &b[i], &k[i]);
  }

  CHT cht;
  for (int i = n - 1; ~i; i--) {
    cht.addLine({-i, a[i]});
  }

  for (int i = 0; i < m; i++) {
    printf("%lld\n", b[i] - cht.query(k[i]));
  }

  return 0;
}