#include <bits/stdc++.h>
using namespace std;

void test_case() {}

int ar[255], val[150][5], dp[200005], bla1[200005], bla2[200005];
char s[255];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int i = 0; i < 26; i++)
  {
    ar['A' + i] = 2 * i;
    ar['a' + i] = 2 * i + 1;
    s[2 * i] = 'A' + i;
    s[2 * i + 1] = 'a' + i;
  }
  memset(val, -1, sizeof val);
  val['B'][2] = 0;
  val['g'][2] = 0;

  val['A'][1] = 0;
  val['a'][1] = 0;
  val['b'][1] = 0;
  val['D'][1] = 0;
  val['d'][1] = 0;
  val['e'][1] = 0;
  val['O'][1] = 0;
  val['o'][1] = 0;
  val['P'][1] = 0;
  val['p'][1] = 0;
  val['Q'][1] = 0;
  val['q'][1] = 0;
  val['R'][1] = 0;

  for (int i = 0; i < 52; i++)
  {
    if (val[s[i]][1] == 0 || val[s[i]][2] == 0) continue;
    val[s[i]][0] = 0;
  }

  for (int i = 0; i < 52; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (val[s[i]][j] == 0) continue;
      int x = (i + 1) % 52, y = 1;
      while (val[s[x]][j] != 0)
      {
        x = (x + 1) % 52;
        y++;
      }
      val[s[i]][j] = y;
    }
    printf("%d %d %d\n", val[s[i]][0], val[s[i]][1], val[s[i]][2]);
  }

  int n, k;
  char str[100005];
  scanf("%d %d %s", &n, &k, str);
  if (k < 0 || k > 2 * n)
  {
    puts("-1");
    exit(0);
  }
  int cur = 0;
  for (int i = 0; i < n; i++)
  {
    if (val[str[i]][0] == 0) cur += 0;
    else if (val[str[i][1]] == 0) cur += 1;
    else cur += 2;
  }
  if (k > cur)
  {}
  return 0;
}