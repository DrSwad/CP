#include <bits/stdc++.h>
using namespace std;
#define hlw ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#include <bits/stdc++.h>
using namespace std;
#define LLMX 0x7fffffffffffffff

long long arr[100005];
long long SegTr[100005 * 3];
int MAX = INT_MAX;

void Build(int nod, int lf, int rt)              //call with nod = 1; lft=1; rgt=N
{
  if (lf == rt)
  {
    SegTr[nod] = arr[lf];
    return;
  }
  int mid = (lf + rt) / 2;

  Build(2 * nod, lf, mid);
  Build(2 * nod + 1, mid + 1, rt);

  SegTr[nod] = min(SegTr[2 * nod], SegTr[2 * nod + 1]);   //range min
  //SegTr[nod] = SegTr[2*nod] + SegTr[2*nod+1];      //range sum
}
int query(int nod, int lf, int rt, int qlf, int qrt)  //query left : qlf; query right: qrt
{
  if (qlf > rt || qrt < lf)                         // Non overlap;
    //return 0;                                       //range Sum
    return MAX;                                         //range min;

  if (qlf <= lf && rt <= qrt)                       //   both left & right falls under range;
    return SegTr[nod];

  int mid = (lf + rt) / 2;
  int a = query(2 * nod, lf, mid, qlf, qrt);
  int b = query(2 * nod + 1, mid + 1, rt, qlf, qrt);
  return min(a, b);     //range min
  //return query(a+b);         //range sum
}

void update(int nod, int lf, int rt, int idx, int val)
{
  if (idx > rt || idx < lf) return;             //out of range
  if (lf == idx && rt == idx)                  //found the node
  {
    SegTr[nod] = val;
    return;
  }
  int mid = (lf + rt) / 2;

  update(2 * nod, lf, mid, idx, val);
  update(2 * nod + 1, mid + 1, rt, idx, val);

  //SegTr[nod] = SegTr[2*nod] + SegTr[2*nod+1];          //range sum
  SegTr[nod] = min(SegTr[2 * nod], SegTr[2 * nod + 1]);    //range min
}

int main()
{
  hlw;
  long long a, b, c, d, f, gg = 0, i, j, m, n, t, mod = 1e9 + 7, l, r;
  cin >> t;
  while (t--)
  {
    cin >> n >> m;
    map<long long, set<long long>> mp;
    for (i = 1; i <= n; i++)
    {
      cin >> arr[i];
      mp[arr[i]].insert(i);
    }
    Build(1, 1, n);
    l = 1;
    r = n;
    set<long long> st = {1};
    while (r > 1)
    {
      a = query(1, 1, n, l, r);
      a = *mp[a].begin();
      st.insert(a);
      r = a - 1;
    }
    while (m--)
    {
      cin >> a >> b;
      arr[a] -= b;
      update(1, 1, n, a, arr[a]);
      if (a > 1)
      {
        d = query(1, 1, n, 1, a - 1);
        if (d <= arr[a]);
        else
        {
          st.insert(a);
          auto it = st.lower_bound(a);
          auto jt = it;
          while (1)
          {
            jt = it;
            jt++;
            if (jt == st.end()) break;
            if (arr[*jt] < arr[a]) break;
            st.erase(jt);

          }

        }

      }
      else
      {
        st.insert(a);
        auto it = st.lower_bound(a);
        auto jt = it;
        while (1)
        {
          jt = it;
          jt++;
          if (jt == st.end()) break;
          if (arr[*jt] < arr[a]) break;
          st.erase(jt);

        }

      }
      cout << st.size();
      if (m) cout << ' ';

    }
    cout << '\n';
  }

  return 0;
}
