#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) scanf("%d", &i);

  vector<int> b;
  for (int i = 0; i < n; i++) {
    if (i == 0) b.push_back(a[i]);
    else if (gcd(a[i], a[i - 1]) > 1) b.push_back(1), b.push_back(a[i]);
    else b.push_back(a[i]);
  }

  printf("%d\n", (int)b.size() - n);
  for (int i = 0; i < b.size(); i++) {
    if (i) printf(" ");
    printf("%d", b[i]);
  }
  puts("");

  return 0;
}