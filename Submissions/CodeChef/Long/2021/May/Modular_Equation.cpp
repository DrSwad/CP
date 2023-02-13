#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

vector<int> divs[N];

void init() {
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divs[j].push_back(i);
    }
  }
}

int main() {
  init();

  int t;
  cin >> t;

  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);

    long long ans = 0;
    for (int b = 2; b <= n; b++) {
      int m0 = m - m % b;
      ans += !m0 ? b - 1 : lower_bound(divs[m0].begin(), divs[m0].end(), b) - divs[m0].begin();
    }

    printf("%lld\n", ans);
  }

  return 0;
}