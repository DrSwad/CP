#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int A = 10;

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
// gp_hash_table<int, int, chash> mp;
// gp_hash_table<ll, int, chash> mp;
// gp_hash_table<pair<int, int>, int, chash> mp;

int n, r;
vector<int> a;
int remaining;
map<vector<int>, int> dp;

bool recurse(int at_group, int capacity_remaining, int tables_remaining) {
  auto state = tuple<int, int, int, vector<int>>{at_group, capacity_remaining, tables_remaining, a};
  if (dp.find(state) != dp.end()) return false;
  dp.insert(state);

  if (remaining == 0) return true;
  if (at_group >= n) at_group = 0, capacity_remaining = r, tables_remaining--;
  if (tables_remaining <= 0) return false;

  if (recurse(at_group + 1, capacity_remaining, tables_remaining)) return true;
  int prev_a = a[at_group];
  while (capacity_remaining > 0 and a[at_group] > 0) {
    capacity_remaining--;
    a[at_group]--;
    remaining--;
    if (a[at_group] < prev_a - 1) {
      if (recurse(at_group + 1, capacity_remaining, tables_remaining)) {
        remaining = remaining - a[at_group] + prev_a;
        a[at_group] = prev_a;
        return true;
      }
    }
  }

  remaining = remaining - a[at_group] + prev_a;
  a[at_group] = prev_a;
  return false;
}

bool check(int tables) {
  dp.clear();
  remaining = accumulate(a.begin(), a.end(), 0);
  return recurse(0, r, tables);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> r;
  a.resize(n);
  for (int &i : a) cin >> i;

  int ans = 1;
  while (!check(ans)) ans++;
  cout << ans << "\n";

  return 0;
}