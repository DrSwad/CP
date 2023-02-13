#include <bits/stdc++.h>
using namespace std;

bool lessOrEq(const vector<int> &v1, const vector<int> &v2) {
  return v1.size() != v2.size() ? v1.size() < v2.size() : v1 <= v2;
}

vector<int> add1(vector<int> v) {
  for (int i = v.size() - 1; ; i--) {
    assert(i >= 0);
    if (v[i] < 9) {
      v[i]++;
      break;
    }
    else v[i] = 0;
  }
  return v;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    vector<vector<int>> v(n);
    for (int i = 0; i < n; i++) {
      while (a[i]) {
        v[i].emplace_back(a[i] % 10);
        a[i] /= 10;
      }
      reverse(v[i].begin(), v[i].end());
    }

    int ans = 0;
    for (int i = 1; i < n; i++) {
      if (!lessOrEq(v[i], v[i - 1])) continue;

      vector<int> _v = vector<int>(v[i - 1].begin(), v[i - 1].begin() + v[i].size());
      bool all9 = true;
      for (int j = v[i].size(); j < v[i - 1].size(); j++) {
        if (v[i - 1][j] != 9) {
          all9 = false;
          break;
        }
      }

      if (v[i] < _v) {
        while (v[i].size() <= v[i - 1].size()) {
          v[i].emplace_back(0);
          ans++;
        }
      } else if (v[i] > _v) {
        while (v[i].size() < v[i - 1].size()) {
          v[i].emplace_back(0);
          ans++;
        }
      } else {
        if (all9) {
          while (v[i].size() <= v[i - 1].size()) {
            v[i].emplace_back(0);
            ans++;
          }
        }
        else {
          ans += v[i - 1].size() - v[i].size();
          v[i] = add1(v[i - 1]);
        }
      }
    }

    printf("Case #%d: %d\n", cs, ans);
  }

  return 0;
}