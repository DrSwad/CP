#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 5;

bool state[N];
bool q_state[N];

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;
  for (int i = 0; i < n; i++) {
    state[i + 1] = s[i] == '1';
  }

  memset(q_state, false, sizeof q_state);

  int q;
  cin >> q;

  while (q--) {
    int b;
    cin >> b;
    q_state[b] = !q_state[b];
  }

  for (int i = 1; i <= n; i++) {
    if (q_state[i]) {
      for (int j = i; j <= n; j += i) {
        state[j] = !state[j];
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (state[i]) {
      ans++;
      for (int j = i; j <= n; j += i) {
        state[j] = !state[j];
      }
    }
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