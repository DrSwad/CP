#include <bits/stdc++.h>
using namespace std;

using std::string;

static struct IO {
	char tmp[1 << 10];

	// fast input routines
	char cur;

//#define nextChar() (cur = getc_unlocked(stdin))
//#define peekChar() (cur)
	inline char nextChar() { return cur = getc_unlocked(stdin); }
	inline char peekChar() { return cur; }

	inline operator bool() { return peekChar(); }
	inline static bool isBlank(char c) { return (c < '-' && c); }
	inline bool skipBlanks() { while (isBlank(nextChar())); return peekChar() != 0; }

	inline IO& operator >> (char & c) { c = nextChar(); return *this; }

	inline IO& operator >> (char * buf) {
		if (skipBlanks()) {
			if (peekChar()) {
				*(buf++) = peekChar();
				while (!isBlank(nextChar())) *(buf++) = peekChar();
			} *(buf++) = 0; } return *this; }

	inline IO& operator >> (string & s) {
		if (skipBlanks()) {	s.clear(); s += peekChar();
			while (!isBlank(nextChar())) s += peekChar(); }
		return *this; }

	inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this;	}

#define defineInFor(intType) \
	inline IO& operator >>(intType & n) { \
		if (skipBlanks()) { \
			int sign = +1; \
			if (peekChar() == '-') { \
				sign = -1; \
				n = nextChar() - '0'; \
			} else \
				n = peekChar() - '0'; \
			while (!isBlank(nextChar())) { \
				n += n + (n << 3) + peekChar() - 48; \
			} \
			n *= sign; \
		} \
		return *this; \
	}

defineInFor(int)
defineInFor(unsigned int)
defineInFor(long long)

	// fast output routines

//#define putChar(c) putc_unlocked((c), stdout)
	inline void putChar(char c) { putc_unlocked(c, stdout); }
	inline IO& operator << (char c) { putChar(c); return *this; }
	inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }

	inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }

	char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
	inline IO& operator << (double d) { return (*this) << toString(d); }


#define defineOutFor(intType) \
	inline char * toString(intType n) { \
		char * p = (tmp + 30); \
		if (n) { \
			bool isNeg = 0; \
			if (n < 0) isNeg = 1, n = -n; \
			while (n) \
				*--p = (n % 10) + '0', n /= 10; \
			if (isNeg) *--p = '-'; \
		} else *--p = '0'; \
		return p; \
	} \
	inline IO& operator << (intType n) { return (*this) << toString(n); }

defineOutFor(int)
defineOutFor(long long)

#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;

typedef long long ll;
const int N = 1e6 + 5;
const int INF = 1e9 + 5;

int n;
int a[N];
pair<int, int> ab[N];
int tree[N << 1];

int merge(int i, int j) {
  if (i == -1) return j;
  else if (j == -1) return i;
  else if (ab[i].second > ab[j].second) return i;
  else return j;
}

void init() {
  for (int i = 0; i < n; ++i) { tree[n + i] = i; }
  for (int i = n - 1; i >= 0; --i) {
    tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }
}

void remove(int p) {
  for (tree[p += n] = -1; p > 1; p >>= 1) {
    tree[p >> 1] = merge(tree[p], tree[p ^ 1]);
  }
}

int query(int l, int r) {
  int ret = -1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = merge(ret, tree[l++]);
    if (r & 1) ret = merge(ret, tree[--r]);
  }
  return ret;
}

bool check(ll M) {
  int took = 0;

  while (took < n) {
    int up = upper_bound(a, a + n, (int)min(M, (ll)INF)) - a;
    int id = query(0, up);

    if (id == -1) return false;

    took++;
    M += ab[id].second - ab[id].first;
    remove(id);
  }

  return true;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &ab[i].first, &ab[i].second);
  }

  sort(ab, ab + n);
  for (int i = 0; i < n; i++) a[i] = ab[i].first;

  ll L = 1, R = 1e15;
  while (L != R) {
    init();
    ll M = (L + R) >> 1;
    if (check(M)) R = M;
    else L = M + 1;
  }

  printf("%lld\n", L);

  return 0;
}