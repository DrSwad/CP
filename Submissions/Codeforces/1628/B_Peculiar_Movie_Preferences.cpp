#include <bits/stdc++.h>
using namespace std;

void answer(bool ans) {
    cout << (ans ? "YES\n" : "NO\n");
}

void test_case() {
    int n;
    cin >> n;

    vector<string> v(n);
    for (auto &s : v) cin >> s;

    for (auto &s : v) {
        if (s.size() == 1) {
            return answer(true);
        }
    }

    set<string> st2, st32, st3;
    for (auto s : v) {
        if (s.length() == 2) {
            if (s[0] == s[1]) {
                return answer(true);
            }

            string need(s.rbegin(), s.rend());
            if (st2.find(need) != st2.end()) {
                return answer(true);
            }
            if (st32.find(need) != st32.end()) {
                return answer(true);
            }

            st2.insert(s);
        }
        else {
            if (s[0] == s.back()) {
                return answer(true);
            }

            string need(s.rbegin(), s.rend());
            if (st3.find(need) != st3.end()) {
                return answer(true);
            }

            need = string(1, s[2]) + string(1, s[1]);
            if (st2.find(need) != st2.end()) {
                return answer(true);
            }

            st3.insert(s);
            st32.insert(s.substr(0, 2));
        }
    }

    return answer(false);
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