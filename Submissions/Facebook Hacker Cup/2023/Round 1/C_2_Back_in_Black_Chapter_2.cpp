#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 5;

bool state[N];

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;
  for (int i = 0; i < n; i++) {
    state[i + 1] = s[i] == '1';
  }

  int cur = 0;
  for (int i = 1; i <= n; i++) {
    if (state[i]) {
      cur++;
      for (int j = 2 * i; j <= n; j += i) {
        state[j] = !state[j];
      }
    }
  }

  long long ans = 0;

  int q;
  cin >> q;

  while (q--) {
    int b;
    cin >> b;

    cur -= state[b];
    state[b] = !state[b];
    cur += state[b];

    ans += cur;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}