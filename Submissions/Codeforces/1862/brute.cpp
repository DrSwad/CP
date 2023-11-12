// Test
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

template<typename T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using i64 = long long;
#define ll long long

const int N = 205 + 5;
const int mod = 1e9 + 7;
const ll inf = 1e16 + 5;

void setIO(string name = "")
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  if (name.size())
  {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

int n, q, a[N], tem, t1, t2, x, y;
map<int, int> mp, dif;

void solve()
{
  mp.clear();
  dif.clear();

  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    mp[a[i]]++;
  }

  {
    auto it = mp.begin();
    tem = it->first;
    it++;
    for ( ; it != mp.end(); it++)
    {
      tem = abs(tem - it->first);
      dif[tem]++;
      tem = it->first;
    }
  }

  cin >> q;
  while (q--)
  {
    cin >> y >> x;
    if (a[y] != x)
    {
      tem = a[y];

      mp[tem]--;
      if (mp[tem] == 0)
      {

        auto it = mp.find(a[y]);
        auto it1 = it;
        it1++;
        if (it1 != mp.end())
        {
          tem = abs(it->first - it1->first);
          dif[tem]--;
          if (dif[tem])
          {}
          else
          {
            it1 = dif.find(tem);
            dif.erase(it1);
          }
        }
        if (it != mp.begin())
        {
          it1 = it;
          it1--;
          tem = abs(it->first - it1->first);
          dif[tem]--;
          if (dif[tem])
          {}
          else
          {
            it1 = dif.find(tem);
            dif.erase(it1);
          }
          it1 = it;
          it1--;
          tem = it1->first;
          it1 = it;
          it1++;

          if (it1 != mp.end())
          {

            tem = abs(tem - it1->first);
            dif[tem]++;
          }
        }
        mp.erase(it);
      }

      a[y] = x;

      if (mp[x]) mp[x]++;
      else
      {
        mp[x]++;
        auto it = mp.find(x);
        auto it1 = it;
        it1++;
        tem = 0;
        if (it1 != mp.end())
        {
          tem = abs(it->first - it1->first);
          dif[tem]++;
          tem = it1->first;
        }

        if (it != mp.begin())
        {

          it1 = it;
          it1--;
          if (tem)
          {

            tem = abs(it1->first - tem);
            dif[tem]--;
            if (dif[tem] == 0)
            {
              auto del = dif.find(tem);
              dif.erase(del);
            }
          }
          tem = abs(it->first - it1->first);
          dif[tem]++;
        }
      }
    }

    auto it = mp.begin();
    t1 = it->first;
    it = mp.end();
    it--;
    t2 = it->first;
    tem = t1 + (t2 - t1);

    if (dif.size())
    {
      auto it = dif.end();
      it--;

      tem += (it->first);
    }
    cout << tem << " \n"[q == 0];
  }
}

int32_t main()
{
  setIO();
  int t = 1, cs = 1;
  cin >> t;

  while (t--)
  {
    // cout << "Case " << cs++ << ": ";
    solve();
  }
  return 0;
}