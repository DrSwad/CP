#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k;
int ans[N];

void construct(int l, int r, int vl, int vr) {
  if (k <= 0 or r - l == 1) {
    iota(ans + l, ans + r, vl);
    return;
  }

  k -= 2;
  int mid = (l + r) / 2;
  int vmid = vr - (mid - l);
  construct(l, mid, vmid, vr);
  construct(mid, r, vl, vmid);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  k--;
  construct(0, n, 0, n);

  if (k != 0) cout << "-1\n";
  else {
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
    }
    cout << "\n";
  }

  return 0;
}