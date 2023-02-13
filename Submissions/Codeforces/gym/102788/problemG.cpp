#include <bits/stdc++.h>
using namespace std;

const int N = 50;

int n;
int a[N];
int a_l[N][N], a_r[N][N];
int grundy[N][N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    a_l[i][0] = a[i];
    a_r[i][0] = a[i];
  }

  for (int chain = 1; chain < n; chain++) {
    for (int i = 1; i < n; i++) {
      if (a_l[i - 1][chain - 1] == 0) continue;
      int g = gcd(a[i], a_l[i - 1][chain - 1]);
      if (g == 1) continue;
      a_l[i][chain] = a[i] / g;
    }

    for (int i = n - 2; i >= 0; i--) {
      if (a_r[i + 1][chain - 1] == 0) continue;
      int g = gcd(a[i], a_r[i + 1][chain - 1]);
      if (g == 1) continue;
      a_r[i][chain] = a[i] / g;
    }
  }

  for (int l = n - 1; l >= 0; l--) {
    for (int r = l + 1; r < n; r++) {
      for (int chain_l = 0; chain_l < n; chain_l++) {
        for (int chain_r = 0; chain_r < n; chain_r++) {
          if (l == r) continue;
          if (a_l[l][chain_l] == 0) continue;
          if (a_r[r][chain_r] == 0) continue;

          set<int> child_grundy;

          for (int mid = l; mid < r; mid++) {
            int val_l = mid == l ? a_l[l][chain_l] : a[mid];
            int val_r = mid + 1 == r ? a_r[r][chain_r] : a[mid + 1];
            if (gcd(val_l, val_r) > 1) {
              int chain_mid = mid + 1 == r ? chain_r + 1 : 1;
              int chain_mid_1 = mid == l ? chain_l + 1 : 1;
              int curr_grundy = grundy[l][mid][chain_l][chain_mid] ^ grundy[mid + 1][r][chain_mid_1][chain_r];
              child_grundy.insert(curr_grundy);
            }
          }

          int mex = 0;
          while (child_grundy.count(mex)) mex++;
          grundy[l][r][chain_l][chain_r] = mex;
        }
      }
    }
  }

  if (grundy[0][n - 1][0][0]) cout << "Alice\n";
  else cout << "Bob\n";

  return 0;
}