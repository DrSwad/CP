#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  set<int> st;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      st.insert(i);
    }
  }

  long long tot = 0;
  for (int i = 0; i < n; i++) {
    auto it = st.lower_bound(i);
    int d = n;
    if (it != st.end()) {
      d = *it - i;
    }
    if (it != st.begin()) {
      it--;
      d = min(d, i - *it);
    }
    tot += d;
  }
  cout << tot << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}