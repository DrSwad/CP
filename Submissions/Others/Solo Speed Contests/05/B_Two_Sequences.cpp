#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> splitVec(vector<int> a, int bt) {
  vector<int> a0, a1;

  for (int av : a) {
    int rest = (av & ((1 << bt) - 1));
    if (av >> bt & 1) a1.push_back(rest);
    else a0.push_back(rest);
  }

  sort(a0.begin(), a0.end());
  sort(a1.begin(), a1.end());

  return {a0, a1};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int ans = 0;

  for (int bt = 0; bt < 29; bt++) {
    auto aa = splitVec(a, bt);
    auto bb = splitVec(b, bt);

    long long cnt = 0;

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int av : aa[i]) {
          int low = lower_bound(bb[j].begin(), bb[j].end(), (1 << bt) - av) - bb[j].begin();
          cnt += i + j & 1 ? low : bb[j].size() - low;
        }
      }
    }

    if (cnt & 1) ans |= 1 << bt;
  }

  cout << ans << endl;

  return 0;
}