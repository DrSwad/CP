#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, q;
int num[2][N], sum[N], carry[N];
set<pair<int, int>> s[10];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  for (int it = 0; it < 2; it++) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    for (int i = 0; i < n; i++) num[it][i] = s[i];
  }

  for (int i = 0; i < n; i++) {
    sum[i] = num[0][i] + num[1][i];
    carry[i] = sum[i] >= 10;
    if (sum[i] >= 10) sum[i] -= 10;
  }



  return 0;
}