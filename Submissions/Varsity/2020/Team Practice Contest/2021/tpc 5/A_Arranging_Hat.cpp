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
const int N = 41;
const int M = 401;
const int MOD = 1e9 + 7;
const int dx[] = {1, -1, 0, 0, -1, -1, 1, 1};
const int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};

/*-------------------------------------------------------------------------------------------------------*/

int cnt[N][N][M][10], n, m;
int dp[N][N][M][10];
int path[N][N][M][10];
bool isSorted[N][N][M];
const int inf = 1e6;

string s[N];

int call(int from, int to, int pos, int dig) {

  if (pos == m) return 0;
  if (dig > 9) return inf;
  if (from == to) {
    if ((s[from][pos] - '0') < dig) {
      path[from][to][pos][dig] = n + 2;
      return 1;
    }
    else return 0;
  }
  if (isSorted[from][to][pos]) {
    bool flag = true;
    for (int i = from; i <= to; i++) flag &= ((s[i][pos] - '0') >= dig);
    if (flag) {
      path[from][to][pos][dig] = n;
      return dp[from][to][pos][dig] = 0;
    }
  }
  if (dp[from][to][pos][dig] != -1) return dp[from][to][pos][dig];

  int ret = call(from, to, pos, dig + 1);
  if (ret != inf) path[from][to][pos][dig] = n + 1;
  vector<int> ans;
  ans.pb(ret);
  for (int _to = from; _to < to; _to++) {
    int cost = (_to - from + 1) - cnt[from][_to][pos][dig] +
               call(from, _to, pos + 1, 0) + call(_to + 1, to, pos, dig + 1);
    // if(from == 2 and to == 4 and pos == 0 and dig == 0) cout << _to << ' ' << cost << '\n';
    if (ret > cost) {
      path[from][to][pos][dig] = _to;
      ret = cost;
    }
    ans.pb(ret);
  }
  // cout << from << ' ' << to << ' ' << pos << ' ' << dig << '\n';
  // for(auto x : ans) cout << x << '\n';
  return dp[from][to][pos][dig] = ret;
}

string ans[N];

void build(int from, int to, int pos, int dig) {
  // ww(from, to, pos, dig, dp[from][to][pos][dig], path[from][to][pos][dig]);
  // cout << from << ' ' << to <<  ' ' << pos << ' ' << dig << '\n';
  // cout << dp[from][to][pos][dig] << ' ' << path[from][to][pos][dig] << '\n';
  if (path[from][to][pos][dig] == -1) return;
  if (path[from][to][pos][dig] == n + 2) {
    // ww(from, to, pos, dig);
    ans[from][pos] = char(dig + '0');
    return;
  }
  if (path[from][to][pos][dig] == n) {
    for (int i = from; i <= to; i++) {
      for (int j = pos; j < m; j++) ans[i][j] = s[i][j];
    }
    return;
  }
  else if (path[from][to][pos][dig] == n + 1) {
    build(from, to, pos, dig + 1);
  }
  else {
    int _to = path[from][to][pos][dig];
    // ww(from, _to, pos, dig, "Cost = ", (_to - from + 1) - cnt[from][_to][pos][dig]);
    // ww(from, to, pos, dig, dp[from][to][pos][dig]);
    for (int i = from; i <= _to; i++) ans[i][pos] = char(dig + '0');
    build(from, _to, pos + 1, 0);
    build(_to + 1, to, pos, dig + 1);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> s[i];

  for (int f = 0; f < n; f++) {
    for (int t = f; t < n; t++) {
      for (int p = 0; p < m; p++) {
        if (t > f) {
          for (int d = 0; d < 10; d++) cnt[f][t][p][d] = cnt[f][t - 1][p][d];
        }
        cnt[f][t][p][s[t][p] - '0']++;
      }
    }
  }

  for (int k = m - 1; k >= 0; k--) {
    for (int i = 0; i < n; i++) {
      isSorted[i][i][k] = 1;
      for (int j = i + 1; j < n; j++) {
        if (s[j - 1][k] < s[j][k]) {
          isSorted[i][j][k] = 1;
        }
        else if (s[j - 1][k] == s[j][k]) {
          if (k == m - 1 or (k < m - 1 and s[j - 1] == s[j] and isSorted[j - 1][j][k + 1])) {
            isSorted[i][j][k] = 1;
          }
          else break;
        }
        else break;
      }
    }
  }

  memset(dp, -1, sizeof dp);
  memset(path, -1, sizeof path);
  cout << call(0, n - 1, 0, 0) << '\n';
  for (int i = 0; i < n; i++) ans[i] = s[i];
  build(0, n - 1, 0, 0);
  for (int i = 0; i < n; i++) cout << i << ' ' << ans[i] << ' ' << s[i] << '\n';
  cout << call(8, 14, 0, 8) << ' ' << call(8, 14, 0, 9) << '\n';
  return 0;
}