#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;
  int len = s.length();

  long long pos;
  cin >> pos;

  vector<char> st;
  int at = 0;

  while (len >= 1) {
    if (pos <= len) {
      if (pos - 1 < (int)st.size()) cout << st[pos - 1];
      else {
        at += (pos - 1) - (int)st.size();
        assert(at < (int)s.size());
        cout << s[at];
      }
      return;
    }
    else {
      while (at < (int)s.size() and (st.empty() or st.back() <= s[at])) {
        st.push_back(s[at]);
        at++;
      }
      assert(!st.empty());
      st.pop_back();
      pos -= len;
      len--;
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
}