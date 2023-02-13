#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define int ll

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;

#define INF 9999999999999999
#define MOD 1000000007
#define all(x) x.begin(), x.end()

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int T; cin >> T;
  while (T--) {
    int N; cin >> N;
    vi A(N); for (auto &i : A) cin >> i;

    sort(all(A)); int ans = INF;

    auto closest_dist = [](auto it1, auto it2, int x) {
      int mini = INF;
      auto it = lower_bound(it1, it2, x);

      if (it < it2) mini = min(mini, abs(x - *it));
      if (next(it) < it2) mini = min(mini, abs(x - *next(it)));
      if (it1 <= prev(it)) mini = min(mini, abs(x - *prev(it)));

      return mini;
    };

    // Case: [a1, aN] [ai, aj]
    for (int i = 1; i < N - 1; i++) {
      int cost = A[N - 1] - A[0] + A[i];
      ans = min(ans, closest_dist(A.begin() + i + 1, A.end() - 1, cost));
    }

    // Case: [a1, aj] [ai, aN]
    for (int i = 1; i < N - 1; i++) {
      int cost = A[N - 1] - A[i] + A[0];
      ans = min(ans, closest_dist(A.begin() + i + 1, A.end() - 1, cost));
    }

    // Case: [a1, ai] [a{i+1}, aN]
    for (int i = 1; i < N - 2; i++) {
      ans = min(ans, abs((A[i] - A[0]) - (A[N - 1] - A[i + 1])));
    }

    // Case: [ai, ai] []
    int jp1 = 0, jp2 = 0;
    for (int i = 0; i < N; i++) {
      jp1 += abs(A[(N - 1) / 2] - A[i]);
      jp2 += abs(A[(N - 1) / 2 + 1] - A[i]);
    }

    for (int i = 0; i < N; i++) {
      if (N & 1) {
        if (i == (N - 1) / 2) ans = min(ans, jp2 - abs(A[(N - 1) / 2 + 1] - A[i]));
        else ans = min(ans, jp1 - abs(A[(N - 1) / 2] - A[i]));

      } else{
        if (i <= (N - 1) / 2) ans = min(ans, jp2 - abs(A[(N - 1) / 2 + 1] - A[i]));
        else ans = min(ans, jp1 - abs(A[(N - 1) / 2] - A[i]));
      }
    }

    cout << ans << endl;
  }

  return 0;
}

/*
   1
   5
   -10000000 -9999388 -9997084 -9988380 10000000
 */