#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  queue<int> q;
  stack<int> st;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i]) q.push(i);
    else st.push(i);
  }

  int ans = 0;
  while (!st.empty() and !q.empty() and q.front() < st.top()) {
    q.pop();
    st.pop();
    ans++;
  }

  cout << ans << "\n";
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