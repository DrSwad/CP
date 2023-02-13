#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int main() {
  int t;
  cin >> t;
  for (int k = 0; k < t; k = k + 1) {
    int n;
    vector<int> v1;
    cin >> n;
    int v = 0, u = 0;
    char a[n + 1], b[n + 1];
    scanf("%s", a);
    for (int i = 0; i < n; i = i + 1) {
      if (a[i] == '1') {
        v = v + 1;
      }
      if (a[i] == '0') {
        u = u + 1;
      }
      if (v == u) {
        v1.push_back(i);
      }
    }
    int m;
    m = v1.size();
    scanf("%s", b);
    int s = 0, p = 0, q = 0, f = 0, c = 0;
    for (int i = 0; i < n && c < m; i = i + 1) {
      if (s == 0) {
        if (a[i] == b[i]) {
          p = 1;
        }
        if (a[i] != b[i]) {
          q = 1;
        }
        s = 1;
        continue;
      }
      if (p == 1) {
        if (a[i] != b[i]) {
          f = 1;
          break;
        }
      }
      if (q == 1) {
        if (a[i] == b[i]) {
          f = 1;
          break;
        }
      }
      if (i == v1[c]) {
        s = 0;
        p = 0;
        q = 0;
        c = c + 1;
      }
    }
    if (m != 0) {
      for (int i = v1[m - 1] + 1; i < n; i = i + 1) {
        if (a[i] != b[i]) {
          f = 1;
          break;
        }
      }
    }
    if (m == 0) {
      for (int i = 0; i < n; i = i + 1) {
        if (a[i] != b[i]) {
          f = 1;
          break;
        }
      }
    }
    if (f == 0) {
      printf("YES\n");
    }
    if (f == 1) {
      printf("NO\n");
    }
  }
  return 0;
}