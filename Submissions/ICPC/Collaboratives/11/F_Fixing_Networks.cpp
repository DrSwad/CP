#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, d, c;
vector<int> e[N];

void constructGroup(int from, int sz) {
  for (int jump = 1; jump <= d / 2; jump++) {
    for (int st = 0; st < jump; st++) {
      int at = st;
      do {
        int nxt = (at + jump) % sz;
        e[from + at].push_back(from + nxt);
        e[from + nxt].push_back(from + at);

        at = nxt;
      } while (at != st);
    }
  }

  if (d % 2 == 1) {
    for (int i = 0; i < sz / 2; i++) {
      int j = i + sz / 2;
      e[from + i].push_back(from + j);
      e[from + j].push_back(from + i);
    }
  }
}

int main() {
  scanf("%d %d %d", &n, &d, &c);

  if (d == 0) {
    if (c == n) {
      puts("Yes");
      for (int i = 1; i <= n; i++) puts("");
    }
    else puts("No");
    return 0;
  }

  if ((long long)c * (d + 1) > n or (n % 2 == 1 and d % 2 == 1) or (d == 1 and n != c * 2)) {
    puts("No");
    return 0;
  }

  puts("Yes");

  for (int i = 0; i < c; i++) {
    int st = i * (d + 1) + 1;
    int en = st + d;
    if (i == c - 1) en = n;

    constructGroup(st, en - st + 1);
  }

  for (int i = 1; i <= n; i++) {
    sort(e[i].begin(), e[i].end());
    for (int j = 0; j < e[i].size(); j++) {
      if (j) printf(" ");
      printf("%d", e[i][j]);
    }
    puts("");
  }

  return 0;
}