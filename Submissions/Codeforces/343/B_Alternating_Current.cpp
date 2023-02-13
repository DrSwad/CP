#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  stack<char> st;
  for (char c : s) {
    if (st.empty() or st.top() != c) st.push(c);
    else st.pop();
  }

  puts(st.empty() ? "Yes" : "No");

  return 0;
}