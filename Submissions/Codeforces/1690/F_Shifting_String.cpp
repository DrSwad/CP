#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> z_function(int n, const T &s) {
  vector<int> z(n, n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    z[i] = (i > r ? 0 : min(r - i + 1, z[i - l]));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

template<typename T>
vector<int> z_function(const T &s) {
  return z_function((int) s.size(), s);
}

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  vector<bool> vis(n, false);
  vector<int> cycles;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      string t;
      while (!vis[i]) {
        vis[i] = true;
        t += s[i];
        i = p[i];
      }

      int sz = t.length();
      vector<int> z = z_function(t + t);
      int len;
      for (len = 1; len < sz; len++) {
        if (z[len] >= sz) break;
      }
      cycles.push_back(len);
    }
  }

  long long ans = cycles[0];
  for (int i : cycles) {
    ans = lcm(ans, (long long)i);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}