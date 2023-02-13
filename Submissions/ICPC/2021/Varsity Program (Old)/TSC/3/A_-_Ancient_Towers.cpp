#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges
#include <bits/stdc++.h>
using namespace std;

inline int input_int() {
  int ret = 0, flag = 1, ip = getchar();
  for ( ; ip < 48 || ip > 57; ip = getchar()) {
    if (ip == 45) {
      flag = -1;
      ip = getchar();
      break;
    }
  }
  for ( ; ip > 47 && ip < 58; ip = getchar()) ret = ret * 10 + ip - 48;
  return flag * ret;
}

struct BIT {
  int n;
  vector<int> f;
  BIT(int n) {
    this->n = n;
    f.resize(this->n + 1, 0);
  }
  void update(int p, int v) {
    p++;
    while (p <= n) f[p] += v, p += p & -p;
  }
  int pref(int p) {
    p++;
    p = min(p, n);
    int ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
};

typedef long long ll;
#define x first
#define y second

const int N = 405;

ll s;
int n;
pair<int, int> p[N];

inline ll signed_area(int i, int j, int k) {
  return ((ll)p[i].x * p[j].y + (ll)p[j].x * p[k].y + (ll)p[k].x * p[i].y) -
         ((ll)p[i].y * p[j].x + (ll)p[j].y * p[k].x + (ll)p[k].y * p[i].x);
}

bool angle_cmp(int i1, int j1, int k1, int i2, int j2, int k2) {
  bool is_up1 = signed_area(i1, j1, k1) > 0;
  bool is_up2 = signed_area(i2, j2, k2) > 0;
  if (is_up1 != is_up2) return is_up1;

  int x11 = p[j1].x - p[i1].x;
  int y11 = p[j1].y - p[i1].y;
  int x12 = p[k1].x - p[i1].x;
  int y12 = p[k1].y - p[i1].y;
  ll d1 = (ll)x11 * x12 + (ll)y11 * y12;
  ll m11 = (ll)x11 * x11 + (ll)y11 * y11;
  ll m12 = (ll)x12 * x12 + (ll)y12 * y12;

  int x21 = p[j2].x - p[i2].x;
  int y21 = p[j2].y - p[i2].y;
  int x22 = p[k2].x - p[i2].x;
  int y22 = p[k2].y - p[i2].y;
  ll d2 = (ll)x21 * x22 + (ll)y21 * y22;
  ll m21 = (ll)x21 * x21 + (ll)y21 * y21;
  ll m22 = (ll)x22 * x22 + (ll)y22 * y22;

  // __int128 left = (__int128)d1 * d1 * m21 * m22 * (d1 > 0 ? 1 : -1);
  // __int128 right = (__int128)d2 * d2 * m11 * m12 * (d2 > 0 ? 1 : -1);
  double left = (double)d1 / sqrt((double)m11) / sqrt((double)m12);
  double right = (double)d2 / sqrt((double)m21) / sqrt((double)m22);
  if (fabs(left - right) < 1e-9) return false;
  if (is_up1) return left > right;
  else return left < right;
}

int main() {
  // ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s;
  s *= 2;

  n = input_int();

  for (int i = 0; i < n; i++) {
    p[i].first = input_int();
    p[i].second = input_int();
  }
  p[n] = {-1, -1};

  int tot_quad = 0;
  int convex_quad = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      p[n] = make_pair(2 * p[j].x - p[i].x, 2 * p[j].y - p[i].y);

      vector<int> rem_ids;
      for (int k = 0; k < n; k++) {
        if (k != i and k != j) {
          rem_ids.push_back(k);
        }
      }

      vector<int> ups1, downs1;
      for (int k : rem_ids) {
        if (signed_area(i, j, k) > 0) ups1.push_back(k);
        else downs1.push_back(k);
      }

      sort(
        ups1.begin(),
        ups1.end(),
        [&](int k1, int k2) {
        return angle_cmp(i, j, k1, i, j, k2);
      }
        );
      sort(
        downs1.begin(),
        downs1.end(),
        [&](int k1, int k2) {
        return angle_cmp(i, j, k1, i, j, k2);
      }
        );

      vector<int> ups2, downs2;
      for (int k : rem_ids) {
        if (signed_area(j, n, k) > 0) ups2.push_back(k);
        else downs2.push_back(k);
      }

      sort(
        ups2.begin(),
        ups2.end(),
        [&](int k1, int k2) {
        return angle_cmp(j, n, k1, j, n, k2);
      }
        );
      sort(
        downs2.begin(),
        downs2.end(),
        [&](int k1, int k2) {
        return angle_cmp(j, n, k1, j, n, k2);
      }
        );

      vector<ll> areas;
      for (int k : downs1) {
        ll A = abs(signed_area(i, j, k));
        areas.push_back(A);
      }
      sort(areas.begin(), areas.end());
      areas.resize(unique(areas.begin(), areas.end()) - areas.begin());
      int sz = areas.size();

      vector<int> area_pre_calc(n);
      for (int k : downs1) {
        ll A = abs(signed_area(i, j, k));
        int a = lower_bound(areas.begin(), areas.end(), A) - areas.begin();
        area_pre_calc[k] = a;
      }
      for (int k : ups1) {
        ll A = abs(signed_area(i, j, k));
        int a = lower_bound(areas.begin(), areas.end(), s - A) - areas.begin();
        area_pre_calc[k] = a;
      }

      {
        BIT bit(sz);

        for (int k : downs1) {
          bit.update(area_pre_calc[k], 1);
        }

        for (int k : ups1) {
          if (area_pre_calc[k] >= sz) tot_quad += 0;
          else if (area_pre_calc[k] == 0) tot_quad += downs1.size();
          else tot_quad += (downs1.size() - bit.pref(area_pre_calc[k] - 1));
        }
      }

      {
        BIT bit(sz);

        for (int ptr_up = 0, ptr_down = 0; ptr_up < ups2.size(); ptr_up++) {
          while (ptr_down < downs2.size() and
                 angle_cmp(j, i, downs2[ptr_down], j, n, ups2[ptr_up])
                 ) {
            int k = downs2[ptr_down];
            bit.update(area_pre_calc[k], 1);
            ptr_down++;
          }

          int k = ups2[ptr_up];
          if (area_pre_calc[k] >= sz) convex_quad += 0;
          else if (area_pre_calc[k] == 0) convex_quad += ptr_down;
          else convex_quad += (ptr_down - bit.pref(area_pre_calc[k] - 1));
        }
      }

      {
        BIT bit(sz);

        p[n] = make_pair(2 * p[i].x - p[j].x, 2 * p[i].y - p[j].y);
        for (int ptr_up = 0, ptr_down = 0; ptr_up < ups1.size(); ptr_up++) {
          while (ptr_down < downs1.size() and
                 angle_cmp(i, n, downs1[ptr_down], i, j, ups1[ptr_up])
                 ) {
            int k = downs1[ptr_down];
            bit.update(area_pre_calc[k], 1);
            ptr_down++;
          }

          int k = ups1[ptr_up];
          if (area_pre_calc[k] >= sz) convex_quad -= 0;
          else if (area_pre_calc[k] == 0) convex_quad -= ptr_down;
          else convex_quad -= (ptr_down - bit.pref(area_pre_calc[k] - 1));
        }
      }
    }
  }

  cout << tot_quad - convex_quad / 2 << "\n";

  return 0;
}