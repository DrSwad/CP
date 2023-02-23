#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    scanf("%d %d", &n, &k);

    vector<ll> a(n), b(n);
    for (ll &i : a) scanf("%lld", &i);

    map<ll, int> mp;
    for (int i = 0; i < k - 1; i++) {
      mp[a[i]]++;
      b[i] = a[i];
    }

    ll ans = 0;
    for (int i = k - 1; i < n; i++) {
      b[i] = a[i] + ans;
      mp[b[i]]++;
      if (i >= k) {
        ll del = b[i - k];
        mp[del]--;
        if (!mp[del]) {
          mp.erase(del);
        }
      }
      ll small = mp.begin()->first;
      ans = small;
    }

    cout << ans << endl;
  }

  return 0;
}