#include <bits/stdc++.h>
using namespace std;

void test_case() {}

int dis[10], dp[105][105][10];
pair<int, int> pnt[10];

int dist(pair<int, int> a, pair<int, int> b)
{
  int x = a.first - b.first, y = a.second - b.second;
  return x * x + y * y;
}

bool chk(int i, int j, int k)
{
  if (i < 0 || i > 100) return 0;
  if (j < 0 || j > 100) return 0;
  if (k == 4) return 1;
  if (dp[i][j][k] != -1) return dp[i][j][k];
  if (dist(pair<int, int>(i, j), pnt[k]) == dis[k])
  {
    return dp[i][j][k] = (chk(i + 1, j, k + 1) | chk(i - 1, j, k + 1) | chk(i, j - 1, k + 1) | chk(i, j + 1, k + 1));
  }
  return dp[i][j][k] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  puts("Q 101 101");
  fflush(stdout);
  scanf("%d", &dis[0]);
  pnt[0].first = 101;
  pnt[0].second = 101;
  pnt[1].first = -1;
  pnt[1].second = 101;
  pnt[2].first = 101;
  pnt[2].second = -1;
  pnt[3].first = -1;
  pnt[3].second = -1;
  puts("Q -1 101");
  fflush(stdout);
  scanf("%d", &dis[1]);

  puts("Q 101 -1");
  fflush(stdout);
  scanf("%d", &dis[2]);

  puts("Q -1 -1");
  fflush(stdout);
  scanf("%d", &dis[3]);
  memset(dp, -1, sizeof dp);
  for (int i = 0; i <= 100; i++)
  {
    for (int j = 0; j <= 100; j++)
    {
      if (chk(i, j, 0))
      {
        printf("A %d %d\n", i, j);
        fflush(stdout);
        exit(0);
      }
    }
  }
  return 0;
}