#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  multiset<int> mb;
  for (int &i : a) scanf("%d", &i);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    mb.insert(x);
    mb.insert(n + x);
  }

  vector<int> c(n);
  for (int i = 0; i < n; i++) {
    c[i] = (*mb.lower_bound(n - a[i])) % n;
    mb.erase(mb.find(c[i]));
    mb.erase(mb.find(c[i] + n));
    (c[i] += a[i]) %= n;
  }

  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", c[i]);
  }
  puts("");

  return 0;
}