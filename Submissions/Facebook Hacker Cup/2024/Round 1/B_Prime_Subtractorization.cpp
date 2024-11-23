#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;

int is_composite[N];

void sieve() {
  is_composite[0] = is_composite[1] = 1;
  for (int p = 2; p * p < N; p++) {
    if (!is_composite[p]) {
      for (int mul = p * p; mul < N; mul += p) {
        is_composite[mul] = 1;
      }
    }
  }
}

void test_case() {
  int n;
  cin >> n;

  if (n < 5) {
    cout << "0\n";
    return;
  }

  int ans = 1;
  for (int p = 2; p <= n; p++) {
    ans += !is_composite[p] and !is_composite[p - 2];
  }

  cout << ans << "\n";
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  sieve();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}