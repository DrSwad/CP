#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int n;
int p[N];
int sub[N];
vector<int> w[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i < n; i++) cin >> p[i], p[i]--;

  long long ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (!w[i].empty()) {
      int mx = *max_element(w[i].begin(), w[i].end());
      if (mx >= sub[i] / 2) {
        ans += 1ll * mx * (sub[i] - mx);
      }
      else {
        vector<int> nw = w[i];

        int best = sub[i] / 2;
        vector<bool> vis(best + 1, false);
        vis[0] = true;
        int sum = 0;
        for (int cw : nw) {
          sum += cw;
          for (int tw = min(sum, best); tw >= cw; tw--) {
            if (!vis[tw]) vis[tw] = vis[tw - cw];
          }
        }
        int left = best;
        while (!vis[left]) left--;
        ans += 1ll * left * (sub[i] - left);
      }
    }

    sub[i]++;
    if (i) {
      sub[p[i]] += sub[i];
      w[p[i]].push_back(sub[i]);
    }
  }

  cout << ans << "\n";

  return 0;
}