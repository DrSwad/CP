#include <bits/stdc++.h>
using namespace std;

int cost(int n, int k, const vector<int> &a) {
  int ret = 0;
  for (int l = 0; l + k <= n; ) {
    vector<bool> vis(k, false);
    bool okay = true;
    for (int i = l; i < l + k; i++) {
      if (vis[a[i]]) {
        okay = false;
        break;
      }
      vis[a[i]] = true;
    }
    if (okay) {
      ret++;
      l += k;
    }
    else l++;
  }
  return ret;
}

int n, k;
vector<int> a;
int ans;
void go(int at) {
  if (at == n) {
    ans += cost(n, k, a);
    return;
  }
  for (int i = 0; i < k; i++) {
    a.push_back(i);
    go(at + 1);
    a.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  go(0);
  cout << ans << "\n";

  return 0;
}