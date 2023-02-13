#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges

#include <bits/stdc++.h>
using namespace std;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch()
    )
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

const int N = 15;
const int MAX_TRIES = 35'000'000;

int n;
int X1[N], Y1[N];
int X2[N], Y2[N];
vector<int> order[N];
bool rem[N];
vector<pair<int, int>> ans;
int perm[N], maps[N];
int tries_left;

long long dist(int i, int j) {
  return (long long)(X1[i] - X2[j]) * (X1[i] - X2[j]) + (long long)(Y1[i] - Y2[j]) * (Y1[i] - Y2[j]);
}

bool go(int i) {
  if (!tries_left) return false;
  tries_left--;
  if (i >= n) return true;
  int at = maps[perm[i]];

  int lst = -1;
  for (int nxt : order[at]) {
    if (rem[nxt]) {
      if (lst != -1 and dist(at, lst) < dist(at, nxt)) break;
      rem[nxt] = false;
      ans.push_back({at, nxt});
      if (go(i + 1)) return true;
      rem[nxt] = true;
      ans.pop_back();
      if (lst == -1) lst = nxt;
    }
  }

  return false;
}

void test_case() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> X1[i] >> Y1[i];
  }
  for (int i = 1; i <= n + 1; i++) {
    cin >> X2[i] >> Y2[i];
  }

  vector<int> random_precedence(n + 2);
  iota(random_precedence.begin(), random_precedence.end(), 1);
  shuffle(random_precedence.begin(), random_precedence.end(), rng);

  for (int i = 1; i <= n; i++) {
    order[i].clear();
    for (int j = 2; j <= n + 1; j++) {
      if (dist(i, j) <= dist(i, 1)) {
        order[i].push_back(j);
      }
    }
    sort(
      order[i].begin(),
      order[i].end(),
      [&](int j, int k) {
      long long d1 = dist(i, j), d2 = dist(i, k);
      if (d1 != d2) return d1 < d2;
      else return random_precedence[j] < random_precedence[k];
    }
      );
  }

  ans.clear();
  fill(rem, rem + N, true);
  tries_left = MAX_TRIES;

  iota(perm, perm + n, 0);
  iota(maps, maps + n, 1);
  sort(
    maps,
    maps + n,
    [&](int i, int j) {
    return dist(i, 1) < dist(j, 1);
  }
    );
  // shuffle(maps, maps + n, rng);
  do {
    if (go(0)) break;
  } while (next_permutation(perm, perm + n));

  if (ans.size()) {
    cout << "POSSIBLE\n";
    for (auto [x, y] : ans) {
      cout << x << " " << y << "\n";
    }
  }
  else {
    cout << "IMPOSSIBLE\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}