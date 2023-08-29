#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 5;

vector<int> prime;
bool is_composite[MAXN];
int sp[MAXN];

void sieve() {
  fill(is_composite, is_composite + MAXN, false);

  for (int i = 2; i < MAXN; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      sp[i] = i;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < MAXN; j++) {
      is_composite[i * prime[j]] = true;
      sp[i * prime[j]] = min(sp[i], prime[j]);
      if (i % prime[j] == 0) break;
    }
  }
}

vector<int> solve(int x) {
  DB();
  debug(x);
  if (x == 1) return {1};

  int SP;
  if (x < MAXN) SP = sp[x];
  else {
    for (SP = 2; SP * SP <= x; SP++) {
      if (x % SP == 0) break;
    }
    if (x % SP != 0) SP = 1;
  }
  debug(SP);

  vector<int> v;
  if (SP < x) v = solve(SP);
  else {
    v = solve(x - 1);
    v.insert(v.begin(), x);
  }
  debug(v);
  int rest = x / SP;
  vector<int> ret;
  for (int i = 0; i < (int)v.size() - 1; i++) {
    ret.push_back(v[i] * rest);
  }
  v = solve(rest);
  debug(rest, v);
  for (int i : v) ret.push_back(i);
  debug(ret);
  return ret;
}

void test_case() {
  int x;
  cin >> x;

  vector<int> ans = solve(x);

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}