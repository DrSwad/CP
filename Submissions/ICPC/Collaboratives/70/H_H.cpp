#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10, LOG_A = 60;

ll basis[LOG_A];

void insertVector(ll mask) {
  for (int i = LOG_A - 1; i >= 0; i--) {
    if ((mask & 1ll << i) == 0) continue;

    if (!basis[i]) {
      basis[i] = mask;
      return;
    }

    mask ^= basis[i];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  while (n--) {
    ll a;
    cin >> a;
    insertVector(a);
  }

  ll ans = 0;

  for (int i = LOG_A - 1; i >= 0; i--) {
    if (!basis[i]) continue;
    if (ans & 1ll << i) continue;
    ans ^= basis[i];
  }

  cout << ans << endl;

  return 0;
}