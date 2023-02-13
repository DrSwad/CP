#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int B = 30;

int n, k;
int a[N];
int msb;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const int RANDOM = (long long)(make_unique<char>().get())
                     ^ chrono::high_resolution_clock::now()
                     .time_since_epoch()
                     .count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) {
    return a * 31 + b;
  }
  int operator()(int x) const { return hash_f(x) ^ RANDOM; }
  int operator()(pair<int, int> x) const {
    return hash_combine(x.first, x.second) ^ RANDOM;
  }
};

pair<int, int> solve_group(const vector<int> &group) {
  gp_hash_table<int, int, chash> group_vis;
  for (int i : group) group_vis[a[i]] = i;

  gp_hash_table<int, int, chash> pref_freq[B];
  for (int b = msb; b >= 0; b--) {
    for (int i : group) {
      pref_freq[b][a[i] >> b] = i;
    }
  }

  for (int i : group) {
    // debug(i);
    int pref = a[i] >> (msb + 1);
    for (int b = msb; b >= 0; b--) {
      pref *= 2;
      // debug(b);
      int a_bit = a[i] >> b & 1;
      int k_bit = k >> b & 1;

      if (k_bit == 0) {
        int npref = pref + (a_bit ^ 1);
        // debug(npref);
        if (pref_freq[b].find(npref) != pref_freq[b].end()) {
          return {i, pref_freq[b][npref]};
        }
      }

      pref += (a_bit ^ k_bit);
    }

    assert(pref ^ a[i] == k);
    if (group_vis.find(pref) != group_vis.end()) {
      return {i, group_vis[pref]};
    }
  }

  return {group.back(), -1};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<int> ans;
  if (k == 0) {
    ans.resize(n);
    iota(ans.begin(), ans.end(), 0);
  }
  else {
    msb = 63 - __builtin_clzll((long long)k);
    // debug(msb);

    map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) {
      groups[a[i] >> (msb + 1)].push_back(i);
    }

    for (auto & [v, group] : groups) {
      auto [v1, v2] = solve_group(group);
      // debug(v, group, curr);
      if (v1 >= 0) ans.push_back(v1);
      if (v2 >= 0) ans.push_back(v2);
    }
  }

  if (ans.size() > 1) {
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
    }
    cout << "\n";
  }
  else cout << "-1\n";

  return 0;
}