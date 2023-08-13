#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define x first
#define y second

template<typename T, class Line = pair<T, T>>
class CHT {
private:
  vector<Line> lines;
  bool maximum;
public:
  CHT(bool maximum = true) { this->maximum = maximum; }
  void addLine(Line line) {
    if (!maximum) line.first = -line.first, line.second = -line.second;
    insert(line);
  }
  T query(const T &x) {
    assert(!lines.empty());

    int L = 0, R = lines.size() - 1;
    while (L != R) {
      int mid1 = L + (R - L) / 3;
      int mid2 = R - (R - L) / 3;
      if (lines[mid1].x * x + lines[mid1].y
          >= lines[mid2].x * x + lines[mid2].y
      ) R = mid2 - 1;
      else L = mid1 + 1;
    }

    T res = lines[L].x * x + lines[L].y;
    return maximum ? res : -res;
  }
private:
  bool bad(const Line &line1, const Line &line2, const Line &line3) {
    return __int128(line3.y - line1.y) * __int128(line1.x - line2.x)
           <= __int128(line2.y - line1.y) * __int128(line1.x - line3.x);
  }
  void insert(const Line &line) {
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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<pair<int, int>> v(n);
  for (auto & [a, b] : v) cin >> a >> b;

  sort(v.begin(), v.end());

  vector<pair<int, int>> nv;
  for (auto [a, b] : v) {
    while (!nv.empty() and nv.back().second <= b) nv.pop_back();
    nv.emplace_back(a, b);
  }
  swap(v, nv);

  int sz = v.size();
  vector<ll> dp(sz);
  CHT<ll> cht(false);

  for (int i = 0; i < sz; i++) {
    ll last_dp = i == 0 ? 0 : dp[i - 1];
    auto [a, b] = v[i];
    cht.addLine({b, last_dp});
    dp[i] = cht.query(a);
  }

  cout << dp[sz - 1] << "\n";

  return 0;
}