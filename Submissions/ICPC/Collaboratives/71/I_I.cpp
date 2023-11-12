#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<string, int> freq;
  while (n--) {
    string name, category;
    cin >> name >> category;
    freq[category]++;
  }

  long long ans = 1;
  for (auto [category, cnt] : freq) {
    ans *= (cnt + 1);
  }

  cout << ans - 1 << "\n";
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