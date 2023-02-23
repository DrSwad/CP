#include <bits/stdc++.h>
using namespace std;

vector<string> get_a(int n) {
  if (n == 1) return {"0", "1"};
  auto pa = get_a(n - 1);
  vector<string> na;
  for (auto s : pa) na.push_back('0' + s);
  for (auto s : pa) na.push_back('1' + s);
  reverse(na.begin() + pa.size(), na.end());
  return na;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<string> a = get_a(n);
  while (k--) {
    s = a[stoi(s, nullptr, 2)];
  }

  cout << s << "\n";

  return 0;
}