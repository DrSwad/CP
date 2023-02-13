#include"bits/stdc++.h"
using namespace std;

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;

struct _ { ios_base::Init i; _() { cin.sync_with_stdio(0); cin.tie(0); cout << fixed << setprecision(10); } } ___;
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
	cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ',');
	cerr.write(names, comma - names) << " : " << arg1 << "  ";
	__f(comma + 1, args...);
}

#define ll long long
#define pii pair<int,int>
#define oset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ff first
#define ss second
#define endll '\n'
#define rep(i,n) for(int i=0;i++<n;)
#define scl(i) scanf("%lld",&i)
#define int long long int
#define all(n) n.begin(),n.end()
#define mem(n,i) memset(n,i,sizeof n)
#define em(a) emplace_back(a)
#define pb(a) push_back(a)
#define srep(it,vv) for(auto &it : vv)
#define prep(it,vv) for(auto it : vv)
#define b_s(a,b) binary_search(a.begin(),a.end(),b)
#define l_b(a,b) lower_bound(a.begin(),a.end(),b)
#define u_b(a,b) upper_bound(a.begin(),a.end(),b)
#define uniq(x) sort(x.begin(),x.end());x.erase(unique(x.begin(),x.end()),x.end())
//vector<vector<int>>arr(n + 5, vector<int>(m + 5,0));

typedef vector<int> vii;
typedef vector<pii> vpp;
typedef vector<string> vss;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r) {
	return uniform_int_distribution<int>(l, r) (rng);
}

const int N = 1e5 + 10;

int n, m, p, q;
int sx, sy, dx, dy;

vii dir(10);

map<pii, vector<pair<pii, int>>>tunel;
map<pii, bool>obs;

const int fx[] = {0, -1, -1, -1, 0, 0, +1, +1, +1}; // Kings Move
const int fy[] = {0, -1, 0, +1, -1, +1, -1, 0, +1}; // Kings Move

signed main()
{
	int __, _ = 0;
	cin >> __;
	for (; _++ < __;)
	{
		obs.clear();
		tunel.clear();
		cin >> n >> m >> p >> q;
		cin >> sx >> sy >> dx >> dy;

		rep(i, 8) cin >> dir[i];

		rep(i, p) {
			int a, b, c, d; cin >> a >> b >> c >> d;
			int w; cin >> w;
			tunel[ {a, b}].push_back({{c, d}, w});
		}

		rep(i, q) {
			int a, b; cin >> a >> b;
			obs[ {a, b}] = true;
		}

		vector<vector<int>>dis(n + 5, vector<int>(m + 5, 0));

		rep(i, n) {
			rep(j, m) {
				dis[i][j] = 1e18;
			}
		}

		priority_queue<pair<pii, pii>>pq;

		dis[sx][sy] = 0;
		pq.push({{0, -1}, {sx, sy}});

		while (pq.size() > 0)
		{
			auto t = pq.top();
			pq.pop();
			int wei = -t.ff.ff;
			int x = t.ss.ff, y = t.ss.ss;


			if (dis[t.ss.ff][t.ss.ss] != wei) continue;

			rep(i, 8) {
				int aa = x + fx[i];
				int bb = y + fy[i];

				int val = dir[i];

				if (i == t.ff.ss) val = 0;

				if (aa<1 or aa>n or bb<1 or bb>m or obs[ {aa, bb}]) continue;

				if (dis[aa][bb] >= dis[x][y] + val) {
					dis[aa][bb] = dis[x][y] + val;
					pq.push({{ -dis[aa][bb], i}, {aa, bb}});
				}
			}

			if (tunel[ {x, y}].size()) {
				vector<pair<pii, int>> vv = tunel[ {x, y}];

				prep(it, vv) {
					int aa = it.ff.ff;
					int bb = it.ff.ss;

					int val = it.ss;

					if (dis[aa][bb] >= dis[x][y] + val) {
						dis[aa][bb] = dis[x][y] + val;
						pq.push({{ -dis[aa][bb], -1}, {aa, bb}});
					}
				}
			}
		}
		cout << "Case " << _ << ": ";
		cout << (dis[dx][dy] == 1e18 ? -1 : dis[dx][dy]) << endll;
	}
}