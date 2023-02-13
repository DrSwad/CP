#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  scanf("%d", &n);
  pair<int, int> ar[n + 5];
  for (int i = 0; i < n; i++)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    ar[i].first = x - y;
    ar[i].second = x + y;
  }
  sort(ar, ar + n);
  for (int xx = 0; xx < 201; xx++)
  {
    int mn = 1000, bla = 1, a = 0, b = 0;
    for (int i = 0; i < n; i++)
    {
      //printf("%d %d\n", ar[i].first, ar[i].second);
      if (ar[i].first > 1000) continue;
      if (ar[i].first == 0)
      {
        puts("No");
        return;
      }
      if (ar[i].first == 1 && ar[i].second == 1)
      {
        if (b)
        {
          puts("No");
          return;
        }
        else
        {
          bla = 1;
          break;
        }

      }
      if (ar[i].first == -1 && ar[i].second == 1)
      {
        if (a)
        {
          puts("No");
          return;
        }
        else
        {
          bla = -1;
          break;
        }

      }
      if (ar[i].first > 0 && ar[i].first < mn && ar[i].first % 2 == 0)
      {
        mn = ar[i].first;
        bla = 1;
      }
      if (ar[i].first < 0 && -1 * ar[i].first < mn && ar[i].first % 2 == 0)
      {
        mn = ar[i].first;
        bla = -1;
      }

    }
    for (int i = 0; i < n; i++)
    {
      ar[i].first += bla;
    }
    for (int i = 0; i < n; i++)
    {
      if (ar[i].first > 0) ar[i].first--;
      else ar[i].first++;
      if (ar[i].first == 0)
      {
        puts("No");
        return;
      }
      ar[i].second--;
      if (ar[i].second == 0) ar[i].first = 100000;
    }
  }
  puts("Yes");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  scanf("%d", &t);

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}