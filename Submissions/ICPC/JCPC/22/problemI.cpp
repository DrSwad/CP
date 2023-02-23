#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
#define ld long double
using namespace std;
int main()
{
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  ll t = 1, n, m, k, a1, b1, c1, len, x, y, z, u, v, p, q, cnt = 0, mx = 0, temp = 0; string s, s1, s2;
  cin >> t;
  while (t--)
  {
    cin >> n >> m >> k;
    ll a[n + 1][m + 1], rowSum[n + 1], colSum[m + 1];
    map<ll, vector<ll>, greater<ll>> mRow, mCol;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
      }
    }
    rowSum[0] = colSum[0] = 0;
    ///row sum
    for (int i = 1; i <= n; i++) {
      cnt = 0;
      for (int j = 1; j <= m; j++) {
        cnt += a[i][j];
      }
      rowSum[i] = cnt;
      mRow[cnt].push_back(i);
      ///cout<<rowSum[i]<<" ";
    }
    ///column sum
    for (int i = 1; i <= m; i++) {
      cnt = 0;
      for (int j = 1; j <= n; j++) {
        cnt += a[j][i];
      }
      colSum[i] = cnt;
      mCol[cnt].push_back(i);
      ///cout<<colSum[i]<<" ";
    }

    ///brute force
    mx = 0;
    for (int i = 0; i <= k; i++) {
      ll row = k - i;
      ll col = i;
      //cout<<"-------------------\n";
      //cout<<row<<" "<<col<<"\n";
      //cout<<"-------------------\n";
      if (row > n or col > m) continue;    ///corner case

      cnt = 0;
      auto it1 = mRow.begin();
      auto it2 = mCol.begin();
      vector<ll> rowIndex, colIndex;
      ///row
      for (int i = 1; i <= row; ) {
        len = it1->second.size();
        if (it1 == mRow.end()) break;
        for (int j = 0; j < len; j++) {
          if (i > row) break;
          ll index = it1->second[j];
          cnt += rowSum[index];
          rowIndex.push_back(index);
          i++;
        }
        it1++;
      }
      ///col
      for (int i = 1; i <= col; ) {
        if (it2 == mCol.end()) break;
        len = it2->second.size();
        for (int j = 0; j < len; j++) {
          if (i > col) break;
          ll index = it2->second[j];
          cnt += colSum[index];
          colIndex.push_back(index);
          i++;
        }
        it2++;
      }

      ///reducing overlapping cells
      ll len1 = rowIndex.size(), len2 = colIndex.size();
      for (int i = 0; i < len1; i++) {
        x = rowIndex[i];
        for (int j = 0; j < len2; j++) {
          y = colIndex[j];
          cnt -= a[x][y];
          ///cout<<x<<" "<<y<<"\n";
        }
      }
      mx = max(mx, cnt);
      ///cout<<cnt<<" "<<mx<<endl<<endl;
    }
    cout << mx << endl;
  }
}
/**
   1
   2 3 1
   1 3 1
   2 4 1
 */
