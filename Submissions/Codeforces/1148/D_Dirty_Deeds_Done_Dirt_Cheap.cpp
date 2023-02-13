#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 3;

int n;
pair<int, int> p[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> p[i].first >> p[i].second;
  }

  vector<int> ids[2];
  for (int i = 0; i < n; i++) {
    bool asc = p[i].first < p[i].second;
    if (!asc) {
      p[i].first = -p[i].first;
      p[i].second = -p[i].second;
    }
    ids[asc].push_back(i);
  }

  vector<int> ans = ids[0].size() > ids[1].size() ? ids[0] : ids[1];
  sort(
    ans.begin(),
    ans.end(),
    [&](const auto&i1, const auto&i2) {
    return p[i1].second > p[i2].second;
  }
    );

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i] + 1;
  }
  cout << "\n";

  return 0;
}