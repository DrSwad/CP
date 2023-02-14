#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOGN = 20;

int n;
int a[N], b[N];
int arr[N];
int st[LOGN][N];

void init() {
  for (int i = 0; i < n; i++) {
    st[0][i] = arr[i];
  }

  for (int i = 1; i < LOGN; i++) {
    for (int j = 0; j < n; j++) {
      st[i][j] = st[i - 1][j];
      if (j + (1 << (i - 1)) < n) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
}

int query(int l, int r) {
  int len = (r - l + 1);
  int i = 31 - __builtin_clz(len);
  return min(st[i][l], st[i][r - (1 << i) + 1]);
}

void test_case() {
  cin >> n;

  for (int i = 0; i < n; i++) cin >> a[i], a[i]--;
  for (int i = 0; i < n; i++) cin >> b[i], b[i]--;

  for (int i = 0; i < n; i++) arr[i] = n;
  for (int i = 0; i < n; i++) {
    arr[a[i]] = min(arr[a[i]], b[i]);
  }

  init();

  vector<int> ans;

  for (int k = 1; k <= n; k++) {
    bool possible = true;
    for (int a = 0; a < n; a += k) {
      possible = possible and query(a, min(n - 1, a + k - 1)) >= a;
    }
    if (possible) ans.push_back(k);
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < (int)ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }
  
  return 0;
}
