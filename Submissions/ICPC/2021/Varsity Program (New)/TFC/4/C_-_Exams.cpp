#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> d(n);
  for (int &i : d) cin >> i, i--;

  vector<int> a(m);
  for (int &i : a) cin >> i;

  function<bool(int)> check = [&](int day) {
    vector<int> last_day(m, -1);
    vector<int> pass_day(day + 1, -1);
    for (int i = 0; i <= day; i++) {
      if (d[i] != -1) {
        if (last_day[d[i]] != -1) {
          pass_day[last_day[d[i]]] = -1;
        }
        last_day[d[i]] = i;
        pass_day[i] = d[i];
      }
    }

    if (find(last_day.begin(), last_day.end(), -1) != last_day.end()) {
      return false;
    }

    for (int i = 0, carry = 0; i <= day; i++) {
      if (pass_day[i] == -1) carry++;
      else {
        if (carry < a[pass_day[i]]) return false;
        carry -= a[pass_day[i]];
      }
    }

    return true;
  };

  int l = 0, r = n;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (check(m)) r = m;
    else l = m;
  }

  cout << (r < n ? r + 1 : -1) << "\n";

  return 0;
}