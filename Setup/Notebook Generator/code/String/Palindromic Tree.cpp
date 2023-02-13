#include <bits/stdc++.h>
 
using namespace std;
 
const int A = 26;
const int N = 300010;
 
char s[N]; long long ans;
int last, ptr, nxt[N][A], link[N], len[N], occ[N];
 
void feed (int at) {
  while (s[at - len[last] - 1] != s[at]) last = link[last];
  int ch = s[at] - 'a', temp = link[last];
  while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
  if (!nxt[last][ch]) {
    nxt[last][ch] = ++ptr, len[ptr] = len[last] + 2;
    link[ptr] = len[ptr] == 1 ? 2 : nxt[temp][ch];
  }
  last = nxt[last][ch], ++occ[last];
}
 
int main() {
  len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  scanf("%s", s + 1);
  for (int i = 1, n = strlen(s + 1); i <= n; ++i) feed(i);
  for (int i = ptr; i > 2; --i) ans = max(ans, len[i] * 1LL * occ[i]), occ[link[i]] += occ[i];
  printf("%lld\n", ans);
  return 0;
}
 
