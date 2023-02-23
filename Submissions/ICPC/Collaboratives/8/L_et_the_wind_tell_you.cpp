#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
#define sz size()
#define SZ(x) int(x.size())
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define quix ios_base::sync_with_stdio(0); cin.tie(0);
#define binary(n, len) cout << bitset<len>(n) << '\n'
#define rr read
#define ww write

//IO

template<typename T>
inline void read(T&t) {
  t = 0; char f = 0, ch = getchar();
  double d = 0.1;
  while (ch > '9' or ch < '0') f |= (ch == '-'), ch = getchar();
  while (ch <= '9' and ch >= '0') t = t * 10 + ch - 48, ch = getchar();
  if (ch == '.') {
    ch = getchar();
    while (ch <= '9' && ch >= '0') t += d * (ch ^ 48), d *= 0.1, ch = getchar();
  }
  t = (f ? -t : t);
}
template<typename T, typename ... Args>
inline void read(T&t, Args&... args) { read(t); read(args ...);}

template<typename T>
void write(T t) { cout << t << '\n'; }
template<typename T, typename ... Args>
void write(T t, Args... args) {
  cout << t << ' '; write(args ...);
}

template<typename T>
void write(std::vector<T> &v) {
  for (int i = 0; i < v.sz; i++) cout << v[i] << " \n"[i == SZ(v) - 1];
}

// Characters and Strings

bool isLetter(char c) { return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');}
bool isUpperCase(char c) { return c >= 'A' and c <= 'Z'; }
bool isLowerCase(char c) { return c >= 'a' and c <= 'z';}
bool isDigit(char c) { return c >= '0' and c <= '9'; }
bool isVowel(char c) { return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u'; }
bool isConsonant(char c) { return !isVowel(c); }

template<class T>
string toString(T n) {
  ostringstream ost;
  ost << n; ost.flush();
  return ost.str();
}

// Bit Hacks

ll setBit(ll mask, int p) { return (mask | (1 << p)); }
ll resetBit(ll mask, int p) { return (mask & ~(1 << p)); }
ll flipBit(ll mask, int p) { return (mask ^ (1 << p)); }
bool check(ll mask, int p) { return (mask & (1 << p)); }

int msb(long long N) { return N ? 63 - __builtin_clzll(N): -1; }
int lsb(long long N) { return __builtin_ffs(N) - 1;}
int countOn(ll mask) { return __builtin_popcountll(mask); }
int countOff(ll mask) { return msb(mask) - countOn(mask) + 1; }

// Math

ll nC2(ll n) { return (n * (n - 1)) / 2; }
ll nc3(ll n) { return (n * (n - 1) * (n - 2)) / 6; }

ll apsum(ll n, ll a = 1, ll d = 1) { return (n * (a + a + (n - 1) * d)) / 2; }

ll lcm(ll a, ll b) { return (a / __gcd(a, b)) * b; }

ll sqr(ll n) { return n * n; }
ll cub(ll n) { return n * n * n; }

template<typename A, typename P>
int bigMod(A a, P p, const int MOD) {
  int ret = 1;
  while (p) {
    if (p & 1) ret = (1LL * ret * a) % MOD;
    a = (1LL * a * a) % MOD;
    p >>= 1LL;
  }
  return ret;
}

template<typename T>
T toBase(T n, T base) {
  T ret = 0LL;
  while (n) {
    ret += n % base;
    ret *= 10LL;
    n /= base;
  }
  return ret;
}

template<class T> struct Fraction {T a, b; Fraction(T a = 0, T b = 1); string toString();};
template<class T> Fraction<T>::Fraction(T a, T b) {T d = __gcd(a, b); a /= d; b /= d; if (b < 0) a = -a, b = -b; this->a = a; this->b = b;}
template<class T> string Fraction<T>::toString() {ostringstream sout; sout << a << " / " << b; return sout.str();}
template<class T> Fraction<T> operator+(Fraction<T> p, Fraction<T> q) {return Fraction<T>(p.a * q.b + q.a * p.b, p.b * q.b);}
template<class T> Fraction<T> operator-(Fraction<T> p, Fraction<T> q) {return Fraction<T>(p.a * q.b - q.a * p.b, p.b * q.b);}
template<class T> Fraction<T> operator*(Fraction<T> p, Fraction<T> q) {return Fraction<T>(p.a * q.a, p.b * q.b);}
template<class T> Fraction<T> operator/(Fraction<T> p, Fraction<T> q) {return Fraction<T>(p.a * q.b, p.b * q.a);}
template<class T> bool operator<(Fraction<T> p, Fraction<T> q) {return 1LL * p.a * q.b < 1LL * p.b * q.a;}
template<class T> bool operator==(Fraction<T> p, Fraction<T> q) {return p.a == q.a and p.b == q.b;}

// Misc

ll rand(ll l, ll r) { //[l, r]
  #ifdef LOCAL
  static mt19937_64 gen;
  #else
  static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
  #endif
  return uniform_int_distribution<ll>(l, r)(gen);
}

template<typename T>
ll sumv(std::vector<T> &v) { return std::accumulate(all(v), 0LL); }

template<typename T>
T minv(std::vector<T> &v) { return *std::min_element(all(v)); }

template<typename T>
T maxv(std::vector<T> &v) { return *std::max_element(all(v)); }

template<typename T>
void make_unique(std::vector<T> &v) { sort(all(v)); v.resize(unique(all(v)) - v.begin()); }

template<typename T>
int lowerBound(std::vector<T> &v, T x) { return lower_bound(all(v), x) - v.begin(); }

template<typename T>
int upperBound(std::vector<T> &v, T x) { return upper_bound(all(v), x) - v.begin(); }

double startTime;
void showCurrentTime() { printf("%.6lf\n", ((double)clock() - startTime) / CLOCKS_PER_SEC); }

/*-------------------------------------------------------------------------------------------------------*/

const double EPS = 1e-9;
const double PI = acos(-1.0);
const int N = 2e5 + 5;
const int MOD = 998244353;
const int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};

/*-------------------------------------------------------------------------------------------------------*/

namespace nCr {
ll factorial[N], invFactorial[N];
ll ncr(ll n, ll r) {
  return (((factorial[n] * invFactorial[r]) % MOD) * invFactorial[n - r]) % MOD;
}
void init() {
  invFactorial[1] = 1;
  for (int i = 2; i < N; i++) invFactorial[i] = MOD - (MOD / i) * invFactorial[MOD % i] % MOD;
  factorial[0] = factorial[1] = invFactorial[0] = 1;
  for (int i = 2; i < N; i++) {
    factorial[i] = (factorial[i - 1] * i) % MOD;
    invFactorial[i] = (invFactorial[i - 1] * invFactorial[i]) % MOD;
  }
}
}

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int n;
bool isLeaf[N];
int sub[N];
ll dp[N], ans[N], root;
vector<int> g[N];

void dfs(int u, int p = 0) {
  sub[u] = 1;
  dp[u] = 1;
  for (auto v : g[u]) {
    if (p == v or isLeaf[v]) continue;
    dfs(v, u);
    sub[u] += sub[v];
    (dp[u] *= nCr::ncr(sub[u] - 1, sub[v]) * dp[v] % MOD) %= MOD;
  }
}

void reroot(int u, int p = 0, ll carry = 1) {
  ans[u] = dp[u] * nCr::ncr(sub[root] - 1, sub[root] - sub[u]) % MOD * carry % MOD;
  for (auto v : g[u]) {
    if (p == v or isLeaf[v]) continue;
    reroot(v, u, ans[u] * binExp(nCr::ncr(sub[root] - 1, sub[v]), -1) % MOD * binExp(dp[v], -1) % MOD);
  }
}

int main() {
  nCr::init();

  scanf("%d", &n);
  if (n == 2) {
    puts("2");
    return 0;
  }

  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    g[x].pb(y); g[y].pb(x);
  }

  root = 1;
  for (int i = 1; i <= n; i++) {
    isLeaf[i] = (g[i].sz == 1);
    if (!isLeaf[i]) root = i;
  }

  dfs(root);
  reroot(root);

  ll final_ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!isLeaf[i]) {
      (final_ans += ans[i]) %= MOD;
    }
  }

  cout << final_ans << endl;

  return 0;
}