#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 8589934592LL;
const int N = 33;

int main() {
  int t;
  cin >> t;

  vector<ll> p2(N);
  p2[0] = 1;
  for (int i = 1; i < N; i++) {
    p2[i] = p2[i - 1] * 2ll % MOD;
  }

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);
    char str[25];
    scanf("%s", str);
    string s(str);

    if (s.length() > 2) printf("%lld\n", MOD - 1);
    else {
      int exp = stoi(s.c_str());
      if (exp >= N) printf("%lld\n", MOD - 1);
      else printf("%lld\n", (p2[exp] + MOD - 1) % MOD);
    }
  }

  return 0;
}