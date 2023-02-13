#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int e[N][26], val[N], freq[N], tot; // N is a constant

void reset() {
  for (int i = 0; i <= tot; i++) {
    val[i] = 0;
    freq[i] = 0;
    for (int j = 0; j < 26; j++) { e[i][j] = 0; }
  }
  tot = 0;
}

bool insert(
    const char *s, int n, int v) { // n is the length of string s
  freq[0]++;
  int u = 0;
  for (int i = 0; i < n; u = e[u][s[i] - 'a'], i++) {
    if (!e[u][s[i] - 'a']) {
      e[u][s[i] - 'a'] = ++tot;
      // Rand(l, r) can generate
      // distinct random numbers in the range of [l, r]
    }
    freq[e[u][s[i] - 'a']]++;
  }
  if (val[u] and val[u] != v) return false;
  val[u] = v;
  return true;
}

int go(int u) {
  // debug() << name(u) name(val[u]) name(freq[u]);
  if (freq[u] == 1) return 1;
  int ret = 1;
  bool flag = false;
  for (int i = 0; i < 26; i++) {
    if (e[u][i]) {
      // debug() << name(u) name(freq[e[u][i]]) name(flag);
      if (!val[u] and freq[e[u][i]] == 1 and !flag) flag = true;
      else {
        ret += go(e[u][i]);
      }
    }
  }
  return ret;
}

int query(const char *s, int n) { // n is the length of string s
  int u = 0;
  for (int i = 0; i < n; u = e[u][s[i] - 'a'], i++)
    if (!e[u][s[i] - 'a']) break;
  return val[u];
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    scanf("%d", &n);

    map<int, string> mp;
    vector<pair<string, int>> queries;
    for (int i = 0; i < n; i++) {
      int v;
      string s;
      cin >> s >> v;
      queries.push_back({s, v});

      if (mp.find(v) != mp.end()) {
        string ps = mp[v];
        string ns;
        for (int i = 0; i < ps.length() and i < s.length(); i++) {
          if (s[i] == ps[i]) {
            ns += s[i];
          } else {
            break;
          }
        }
        mp[v] = ns;
      } else {
        mp[v] = s;
      }
    }

    printf("Case #%d: ", cs);
    bool flag = true;
    for (auto [v, s] : mp) {
      flag = flag and insert(s.c_str(), s.length(), v);
    }
    for (auto [s, v] : queries) {
      flag = flag and query(s.c_str(), s.length()) == v;
    }
    // debug() << name(mp);
    if (!flag) {
      puts("-1");
    } else {
      printf("%d\n", go(0));
    }

    reset();
  }

  return 0;
}