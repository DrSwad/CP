#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<int, int> freq;
  while (n--) {
    int a;
    cin >> a;
    freq[a]++;
  }

  if (freq.size() == 1 or (freq.size() == 2 and abs(freq.begin()->second - freq.rbegin()->second) <= 1)) {
    cout << "Yes\n";
  }
  else cout << "No\n";
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