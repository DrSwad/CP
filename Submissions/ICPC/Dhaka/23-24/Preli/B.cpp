// (A - 1) * q + r, 0 <= r < (A - 1)
// |r - (r - q) % A| = |r - (r - qq) % A|, qq = q % A

// r = A - 2, r - (r - qq) = qq
// ...
// r = qq, r - (r - qq) = qq
// r = qq - 1, (r - qq) % A = A - 1, (r - qq) % A - r = A - qq
// ...
// r = 0, (r - qq) % A = A - qq, (r - qq) % A - r = A - qq

// sum(|r - (r - q) % A|), 0 <= r < (A - 1)
// = qq * (A - qq - 1) + (A - qq) * qq
// = qq * A - qq**2 - qq + qq * A - qq**2
// = qq * 2A - 2 * qq**2 - qq

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll A, N;
  cin >> A >> N;

  ll ans = 0;

  ll full_q = N / (A - 1);
  if ((A - 1) * full_q + (A - 2) > N) full_q--;

  {
    ll terms = A;
    ans += ((full_q + 1) / A) * (terms * (terms - 1) / 2 * (2 * A - 1) - terms * (terms - 1) * (2 * terms - 1) / 3);
  }

  {
    ll terms = (full_q + 1) % A;
    ans += (terms * (terms - 1) / 2 * (2 * A - 1) - terms * (terms - 1) * (2 * terms - 1) / 3);
  }

  {
    ll q = full_q + 1;
    ll qq = q % A;
    ll max_r = N - (A - 1) * q;
    ans += min(max_r + 1, qq) * (A - qq);
    if (max_r > qq - 1) ans += (max_r - (qq - 1)) * qq;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}