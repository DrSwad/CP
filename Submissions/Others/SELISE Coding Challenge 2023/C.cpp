#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int L = 60;
const int Q = 7;
const int WA = 3;

int dp[L][Q + 1][WA + 1];

bool query(ll x) {
  cout << "? " << x << endl;
  string ret;
  cin >> ret;
  return ret == "yes";
}

void answer(ll ans) {
  cout << "! " << ans << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  for (int q = 0; q <= Q; q++) {
    for (int wa = 0; wa <= WA; wa++) {
      dp[0][q][wa] = -1;
    }
  }

  for (int l = 1; l < L; l++) {
    for (int q = 0; q <= Q; q++) {
      for (int wa = 0; wa <= WA; wa++) {
        for (int nl = 1; nl <= l; nl++) {
          if (q > 0 and dp[l - nl][q - 1][wa] and (wa > 0 and dp[nl - 1][q - 1][wa - 1])) {
            dp[l][q][wa] = nl;
            break;
          }
        }
      }
    }
  }

  int l = 0, r = L - 1;
  int q = 7;
  int wa = 3;
  while (l < r) {
    int nl = l + dp[r - l][q][wa];
    if (query(1ll << nl)) l = nl;
    else r = nl - 1;
  }

  assert(l == r);
  answer(1ll << l);

  return 0;
}
