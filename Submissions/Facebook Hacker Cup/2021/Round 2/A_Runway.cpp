#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int nr, np;
  cin >> nr >> np;

  vector<int> is(np);
  for (int &s : is) cin >> s;

  vector<vector<int>> r(nr, vector<int>(np));
  for (int i = 0; i < nr; i++) {
    for (int &s : r[i]) cin >> s;
  }

  int tot = 0;
  map<int, int> cs, fs, ds;
  for (int s : is) cs[s]++, fs[s]++;

  for (int i = 0; i < nr; i++) {
    map<int, int> ns;
    for (int s : r[i]) ns[s]++;

    for (auto [s, f] : cs) {
      int dec = max(0, cs[s] - (ns.find(s) == ns.end() ? 0 : ns[s]));
      tot += dec;
      if (fs.find(s) != fs.end()) {
        ds[s] += dec;
      }
    }

    swap(cs, ns);
    ns.clear();
  }

  int mx = 0;
  for (auto [s, dec] : ds) mx += min(fs[s], dec);

  cout << tot - mx << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}