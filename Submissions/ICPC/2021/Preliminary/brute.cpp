#include <bits/stdc++.h>
using namespace std;

void test_case() {
  vector<string> s(2);
  cin >> s[0] >> s[1];

  int m;
  cin >> m;

  while (m--) {
    int type;
    cin >> type;

    if (type == 1 or type == 2) {
      int id = type - 1;

      int l, r;
      cin >> l >> r;

      char ch;
      cin >> ch;
      int c;
      c = ch - 'a';

      for (int i = l - 1; i < r; i++) {
        s[id][i] = 'a' + c;
      }
    }
    else {
      int l1, r1, l2, r2;
      cin >> l1 >> r1 >> l2 >> r2;

      set<string> st;
      {
        int i1 = l1 - 1;
        for (int j1 = i1 + 1; j1 <= r1; j1++) {
          st.insert(s[0].substr(i1, j1 - i1));
          {
            int j2 = r2;
            for (int i2 = l2 - 1; i2 < r2; i2++) {
              st.insert(s[1].substr(i2, j2 - i2));
              st.insert(s[0].substr(i1, j1 - i1) + s[1].substr(i2, j2 - i2));
            }
          }
        }
      }
      // debug(st);

      cout << st.size() + 1 << "\n";
    }
  }
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