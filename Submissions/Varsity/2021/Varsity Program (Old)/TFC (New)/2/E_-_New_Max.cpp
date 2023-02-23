#include <bits/stdc++.h>
using namespace std;

void answer(bool ans) {
  cout << (ans ? "YES" : "NO") << "\n";
}

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (k == 0) return answer(*max_element(a.begin(), a.end()) == m);
  else {
    int mx_cnt = 0;
    for (int i : a) {
      mx_cnt += i > m;
    }

    if (mx_cnt > 0) return answer(mx_cnt <= k);
    else return answer(true);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}