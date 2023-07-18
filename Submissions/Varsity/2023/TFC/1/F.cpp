#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  unordered_map<int, int> freq;
  for (int &i : a) cin >> i, freq[i]++;

  multiset<int> st;
  for (auto [val, cnt] : freq) {
    st.insert(cnt);
  }

  int ans = 0;
  while (st.size() > 1) {
    int val1 = *prev(st.end()); st.erase(prev(st.end()));
    int val2 = *prev(st.end()); st.erase(prev(st.end()));
    ans++;
    if (val1 > 1) st.insert(val1 - 1);
    if (val2 > 1) st.insert(val2 - 1);
  }
  if (!st.empty()) ans += *st.begin();

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}