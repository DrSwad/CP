#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

void test_case() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  for (int &i: a) scanf("%d", &i);

  vector<int> dp(n);
  dp[n - 1] = 0;
  stack<int> st;
  st.push(n - 1);

  for (int i = n - 2; ~i; i--) {
    dp[i] = N;
    while (!st.empty() and a[st.top()] < a[i]) {
      dp[i] = min(dp[i], 1 + dp[st.top()]);
      st.pop();
    }

    if (st.empty() or a[st.top()] > a[i]) {
      st.push(i);
    } else {
      dp[i] = min(dp[i], 1 + dp[st.top()]);
      if (dp[i] < dp[st.top()]) {
        st.pop();
        st.push(i);
      }
    }
  }

  printf("%d\n", dp[0] < N ? dp[0] : -1);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}