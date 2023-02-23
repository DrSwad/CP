#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include <stack>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef double db;

#define mp make_pair
#define pb push_back
#define pt(i) printf("%lld\n", (ll)i)
#define mp make_pair
#define ff first
#define ss second
#define pi acos(-1.0)
#define CLR(a)          memset(a, 0, sizeof(a))
#define SET(a)          memset(a, -1, sizeof(a))

ll in() { ll a; scanf("%lld", &a); return a;}
db din() { db a; scanf("%lf", &a); return a; }
ll bigmod(ll b, ll p, ll md) {if (p == 0) return 1; if (p % 2 == 1) { return ((b % md) * bigmod(b, p - 1, md)) % md;} else {ll y = bigmod(b, p / 2, md); return (y * y) % md;}}
ll gcd(ll a, ll b) { if (b == 0) return a; else return gcd(b, a % b); }

long long getRandom(long long a, long long b) {
  long long ret = (long long)rand() * (long long)rand();
  ret %= (b - a + 1);
  ret += a;
  return ret;
}

int main()
{
  int n = in();
  pair<string, int> ar[n + 5];
  for (int i = 0; i < n; i++) cin >> ar[i].ff >> ar[i].ss;
  for (int i = 0; i < n; i++)
  {
    if (ar[i].ff[0] == 'y')
    {
      int mx = 0;
      for (int j = i + 1; j < n && mx <= ar[i].ss; j++)
      {
        if (ar[j].ff[0] == 'n') mx = max(mx, ar[j].ss);
        else if (ar[j].ss > mx)
        {
          ar[i].ss = min(ar[i].ss, ar[j].ss);
        }
      }
      mx = 0;
      for (int j = i - 1; j >= 0 && mx <= ar[i].ss; j--)
      {
        if (ar[j].ff[0] == 'n') mx = max(mx, ar[j].ss);
        else if (ar[j].ss > mx)
        {
          ar[i].ss = min(ar[i].ss, ar[j].ss);
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    if (ar[i].ff[0] == 'y' && ar[i].ss != -1)
    {
      ans++;
      for (int j = i + 1; j < n; j++)
      {
        if (ar[j].ff[0] == 'n' && ar[j].ss >= ar[i].ss) break;
        if (ar[i].ss == ar[j].ss) ar[j].ss = -1;
      }
    }
  }
  pt(ans);
}