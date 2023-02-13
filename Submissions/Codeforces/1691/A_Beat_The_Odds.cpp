#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int cnt[2] = {0};
  while (n--) {
    int i;
    cin >> i;
    cnt[i & 1]++;
  }

  cout << min(cnt[0], cnt[1]) << "\n";
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