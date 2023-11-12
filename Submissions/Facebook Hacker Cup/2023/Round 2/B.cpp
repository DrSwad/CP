#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
array<vi, 2> manacher(const vi &s) {
  int n = s.size();
  array<vi, 2> p = {vi(n + 1), vi(n)};
  for (int z = 0; z < 2; z++) for (int i = 0, l = 0, r = 0; i < n; i++) {
      int t = r - i + !z;
      if (i < r) p[z][i] = min(t, p[z][l + t]);
      int L = i - p[z][i], R = i + p[z][i] - !z;
      while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
      if (R > r) l = L, r = R;
    }
  return p;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  vector<int> c(4 * n);
  for (int i = 0; i < n; i++) c[0 * n + i] = a[i];
  for (int i = 0; i < n; i++) c[1 * n + i] = b[i];
  for (int i = 0; i < n; i++) c[2 * n + i] = a[i];
  for (int i = 0; i < n; i++) c[3 * n + i] = b[i];

  auto res = manacher(c);

  int half = n / 2;
  multiset<int> st1, st2;
  for (int i = 0; i < half - 1; i++) {
    st1.insert(c[n + i] - c[i]);
  }
  for (int i = 1; i < half; i++) {
    st2.insert(c[2 * n - 1 - i] - c[n - 1 - i]);
  }

  int ans = -1;

  for (int st = 0; st < 2 * n; st++) {
    if (st > 0) {
      st1.erase(st1.find(c[(st - 1) + n + 0] - c[(st - 1) + 0]));
      st2.erase(st2.find(c[(st - 1) + 2 * n - 1 - (half - 1)] - c[(st - 1) + n - 1 - (half - 1)]));
    }

    st1.insert(c[st + n + (half - 1)] - c[st + (half - 1)]);
    st2.insert(c[st + 2 * n - 1 - 0] - c[st + n - 1 - 0]);

    if (*st1.begin() > 0 and * st2.rbegin() < 0 and res[0][st + n] >= n) {
      ans = st;
      break;
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