#include <bits/stdc++.h>
using namespace std;

const int N = 21;

int C[N][N];

void init() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 or j == i) C[i][j] = 1;
      else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
}

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> freq(26, 0);
  for (char c : s) freq[c - 'a']++;

  int odd_count = 0;
  for (int c = 0; c < 26; c++) {
    odd_count += freq[c] % 2 == 1;
  }

  if (odd_count > 1) {
    cout << "0\n";
    return;
  }

  long long ans = 1;
  n /= 2;
  for (int c = 0; c < 26; c++) {
    ans *= C[n][freq[c] / 2];
    n -= freq[c] / 2;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}