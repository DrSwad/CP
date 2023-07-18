#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> freq(10, 0);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    freq[a - 1]++;
  }

  vector<int> freq2(n + 1, 0);
  for (int i = 0; i < 10; i++) {
    freq2[freq[i]]++;
  }

  int mx = *max_element(freq2.begin() + 1, freq2.end());
  for (int i = 1; i <= n; i++) {
    if (freq2[i] == mx) {
      cout << i << "\n";
      return;
    }
  }

  assert(false);
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
}//