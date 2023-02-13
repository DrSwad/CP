#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
#define x first
#define y second
const ll PRECISION = 1e9;
const ll PRECISION_DIGITS = 7;

point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y);
}

ll cross(const point &a, const point &b) {
  return a.x * b.y - a.y * b.x;
}

bool orient(const point &a, const point &b, const point &c) {
  return cross(b - a, c - a) >= 0;
}

void test_case() {
  int n;
  cin >> n;

  vector<point> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld", &p[i].x, &p[i].y);
  }
  vector<point> q;
  for (int i = 0; i < n; i++) {
    if (i and p[i - 1].x == p[i].x) continue;
    q.push_back(p[i]);
  }
  p = q;
  n = p.size();

  if (n == 1) {
    cout << "0\n";
    return;
  }

  ll ans_int = 0, ans_float = 0;
  function<void(int, int)> consider = [&](int i, int j) {
    ll up = (p[i].y - p[j].y) * p[j].x;
    ll down = p[j].x - p[i].x;
    assert(down > 0);

    bool positive = up >= 0;
    if (!positive) up = -up;

    ll curr_int = up / down;
    assert(up >= 0);
    if (up) up %= down;
    ll curr_float = up * PRECISION / down;

    if (!positive) {
      curr_int = -curr_int;
      if (curr_float) {
        curr_int--;
        curr_float = PRECISION - curr_float;
      }
    }

    curr_int += p[j].y;

    if (curr_int < 0) return;

    if (ans_int < curr_int or (ans_int == curr_int and ans_float < curr_float)) {
      ans_int = curr_int;
      ans_float = curr_float;
    }
  };

  vector<int> st;
  st.push_back(0);

  for (int i = 1; i < n; i++) {
    while (st.size() > 1 and orient(p[i], p[st[st.size() - 2]], p[st[st.size() - 1]])) {
      st.pop_back();
    }
    consider(st.back(), i);
    st.push_back(i);
  }

  printf("%lld.%09lld\n", ans_int, ans_float);
  // cout << ans_int << "." << setw(PRECISION_DIGITS) << ans_float << "\n";
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);
  // cout << setfill('0');

  int t = 1;
  scanf("%d", &t);
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}