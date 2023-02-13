#include <bits/stdc++.h>
using namespace std;

int count_palindrome_substrings(string s) {
  int n = s.length();
  int ret = 0;

  for (int i = 0; i < n; i++) {
    ret++;
    for (int l = i - 1, r = i + 1; l >= 0 and r < n and s[l] == s[r]; l--, r++) {
      ret++;
    }
    for (int l = i, r = i + 1; l >= 0 and r < n and s[l] == s[r]; l--, r++) {
      ret++;
    }
  }

  return ret;
}

void test_case() {
  int n, q;
  cin >> n >> q;

  map<string, int> si;
  vector<int> palindromes(n);

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    si[s] = i;
    palindromes[i] = count_palindrome_substrings(s);
  }

  while (q--) {
    string a, b;
    cin >> a >> b;

    int ia = si[a];
    int ib = si[b];
    if (ia > ib) swap(a, b), swap(ia, ib);

    if (palindromes[ia] >= palindromes[ib]) cout << ia + 1 << "\n";
    else cout << ib + 1 << "\n";
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