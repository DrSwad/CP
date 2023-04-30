#include <bits/stdc++.h>
using namespace std;

const int A = 10000;
typedef long long ll;

int main() {
  int n;
  scanf("%d", &n);

  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    scanf(" 0.%lld", &a[i]);
  }

  auto check = [&](const vector<ll> &b) {
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      if (b[i] < 1 or b[i] > A) return false;
      sum += 1ll * b[i] * b[i];
    }

    double down = sqrt(sum);
    for (int i = 0; i < n; i++) {
      ll val = b[i] / down * 1e12;
      if (abs(a[i] - val) > 1e6) return false;
    }

    return true;
  };

  bool okay = false;
  vector<ll> b(n);
  for (int d0 = 1; d0 <= A and !okay; d0++) {
    ll g0 = a[0] / d0;
    for (ll g = max(1ll, g0 - 5); g <= g0 + 5; g++) {
      for (int i = 0; i < n; i++) b[i] = a[i] / g;
      if (check(b)) {
        okay = true;
        break;
      }
    }
  }
  
  assert(okay);

  for (int i = 0; i < n; i++) {
    printf("%lld\n", b[i]);
  }

  return 0;
}
