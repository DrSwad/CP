#include <bits/stdc++.h>
using namespace std;

pair<string, string> format(int m) {
  int h = m / 60;
  m %= 60;
  string sh = to_string(h);
  if (sh.length() < 2) sh = "0" + sh;
  string sm = to_string(m);
  if (sm.length() < 2) sm = "0" + sm;
  return {sh, sm};
}

bool check(int m) {
  auto [sh, sm] = format(m);
  return sh[0] == sm[1] and sh[1] == sm[0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int h, m;
  char colon;
  cin >> h >> colon >> m;

  m += h * 60;
  const int M = 24 * 60;

  m = (m + 1) % M;
  while (!check(m)) {
    m = (m + 1) % M;
  }

  auto [sh, sm] = format(m);
  cout << sh << ":" << sm << "\n";

  return 0;
}