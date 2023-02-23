#include <bits/stdc++.h>
using namespace std;

pair<bool, bool> query(int a, int b) {
  assert(a != b);
  a++, b++;
  cout << "? " << a << " " << b << endl;
  char ra, rb;
  while (cin >> ra, ra != '+' and ra != '-');
  while (cin >> rb, rb != '+' and rb != '-');
  return {ra == '+', rb == '+'};
}

void answer(vector<int> ans) {
  sort(ans.begin(), ans.end());
  assert(unique(ans.begin(), ans.end()) == ans.end());
  cout << "! " << ans.size();
  for (int i : ans) cout << " " << i + 1;
  cout << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  int n;
  cin >> n;

  vector<int> ids(n);
  iota(ids.begin(), ids.end(), 0);

  int good;
  while (true) {
    int n = ids.size();
    if (n <= 2) {
      good = ids.back();
      break;
    }
    vector<int> nids;
    for (int i = 0; i < n / 2; i++) {
      auto [res1, res2] = query(ids[i << 1], ids[i << 1 | 1]);
      if (res1 and res2) nids.push_back(ids[i << 1]);
    }
    if (nids.empty()) {
      good = ids.back();
      break;
    }
    if (n % 2 == 1 and nids.size() % 2 == 0) nids.push_back(ids.back());
    swap(ids, nids);
    n = ids.size();
  }

  vector<int> ans(1, good);
  for (int i = 0; i < n; i++) {
    if (i != good) {
      auto [res1, res2] = query(good, i);
      if (res1) ans.push_back(i);
    }
  }

  answer(ans);

  return 0;
}