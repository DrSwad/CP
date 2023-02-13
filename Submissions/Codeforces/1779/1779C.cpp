#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int solve(vector<int> v) {
  v.pop_back();

  ll pref = 0;
  priority_queue<int> pq;
  int moves = 0;

  for (int i : v) {
    if (i < 0) pq.push(2 * -i);
    pref += i;
    while (pref < 0) {
      pref += pq.top();
      pq.pop();
      moves++;
    }
  }

  return moves;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> v(n);
  for (int &i : v) cin >> i;

  int ans = 0;

  {
    vector<int> v2(v.begin(), v.begin() + m);
    reverse(v2.begin(), v2.end());
    for (int &i : v2) i = -i;
    ans += solve(v2);
  }

  {
    vector<int> v2(v.begin() + m, v.end());
    v2.push_back(0);
    ans += solve(v2);
  }

  cout << ans << "\n";
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