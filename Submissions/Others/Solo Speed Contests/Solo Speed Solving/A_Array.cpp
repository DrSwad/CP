#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  scanf("%d %d", &n, &k);

  vector<int> a(n);
  for (int &i : a) scanf("%d", &i);

  map<int, int> freq;
  for (int i : a) freq[i]++;

  auto include = [&](int index) {
    if (index < 0 or index >= a.size()) return;
    freq[a[index]]++;
  };
  auto remove = [&](int index) {
    if (index < 0 or index >= a.size()) return;
    freq[a[index]]--;
    if (!freq[a[index]]) freq.erase(a[index]);
  };

  int l = 0, r = n - 1;
  while (l <= r and freq.size() >= k) remove(l++);
  include(--l);
  while (l <= r and freq.size() >= k) remove(r--);
  include(++r);

  if (freq.size() != k) l = r = -1;
  else l++, r++;
  printf("%d %d", l, r);

  return 0;
}