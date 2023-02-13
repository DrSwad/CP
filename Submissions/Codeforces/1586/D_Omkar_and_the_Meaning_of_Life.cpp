#include <bits/stdc++.h>
using namespace std;

int query(const vector<int>&v) {
  cout << "?";
  for (int i : v) cout << " " << i;
  cout << endl;
  int res;
  cin >> res;
  return res;
}

void answer(const vector<int>&v) {
  cout << "!";
  for (int i : v) cout << " " << i;
  cout << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> p(n);
  p[n - 1] = n;
  while (p[n - 1] > 1) {
    vector<int> vq = vector<int>(n, p[n - 1]);
    vq[n - 1] = 1;
    int res = query(vq);
    if (res != 0) break;
    p[n - 1]--;
  }

  for (int val = 1; val <= n; val++) {
    if (val == p[n - 1]) continue;

    vector<int> vq = vector<int>(n, p[n - 1]);
    vq[n - 1] = val;
    int res = query(vq);
    assert(res);

    p[res - 1] = val;
  }

  answer(p);

  return 0;
}