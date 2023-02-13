#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b, ab, ba;
  cin >> a >> b >> ab >> ba;

  string s;
  cin >> s;
  int n = s.length();

  int ca = count(s.begin(), s.end(), 'A');
  if (ca != a + ab + ba) {
    cout << "NO\n";
    return;
  }

  vector<int> cnt[2][2];
  for (int l = 0; l < n; ) {
    int r = l;
    int need = s[l] - 'A';
    while (r < n and s[r] == 'A' + need) r++, need ^= 1;

    int len = r - l;
    cnt[s[l] - 'A'][len % 2].push_back(len);

    l = r;
  }

  sort(cnt[0][0].begin(), cnt[0][0].end());
  for (int len : cnt[0][0]) {
    int take = min(len / 2, ab);
    ab -= take;
    if (ab == 0 and take < len / 2) {
      int rem = len / 2 - 1 - take;
      ba -= rem;
    }
  }

  sort(cnt[1][0].begin(), cnt[1][0].end());
  for (int len : cnt[1][0]) {
    int take = min(len / 2, ba);
    ba -= take;
    if (ba == 0 and take < len / 2) {
      int rem = len / 2 - 1 - take;
      ab -= rem;
    }
  }

  int tot = 0;
  for (int len : cnt[0][1]) tot += len / 2;
  for (int len : cnt[1][1]) tot += len / 2;
  if (tot >= ab + ba) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}