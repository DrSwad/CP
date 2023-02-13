#include <bits/stdc++.h>
using namespace std;

const int A = 26;
const int N = 100010;
char s[N]; // 1-indexed
int last, ptr, nxt[N][A], link[N], len[N], occ[N], depth[N], end_at[N];
int ans;
void feed(int at) {
  while (s[at - len[last] - 1] != s[at]) last = link[last];
  int ch = s[at] - 'a', temp = link[last];
  while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
  if (!nxt[last][ch]) {
    nxt[last][ch] = ++ptr, len[ptr] = len[last] + 2;
    link[ptr] = len[ptr] == 1 ? 2 : nxt[temp][ch];
    depth[ptr] = depth[link[ptr]] + 1;
    ans = max(ans, len[ptr]);
  }
  last = nxt[last][ch], ++occ[last];
  end_at[at] = depth[last];
}

int main() {
  int n;
  scanf("%d %s", &n, s + 1);
  len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  for (int i = 1; i <= n; ++i) feed(i);
  cout << ans << endl;

  return 0;
}