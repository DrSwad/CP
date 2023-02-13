#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

string s[2], x;
int ns[2], nx;
int z[2][N << 1];
int sa[N], lcp[N], rnk[N];
vector<int> q[N][2];
long long tree[N << 2];
int lazy[N << 2];
long long ans = 1;

unsigned char mask[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
#define tget(i) ((t[(i) / 8] & mask[(i) % 8]) ? 1 : 0)
#define tset(i, b) t[(i) / 8] = (b) ? (mask[(i) % 8] | t[(i) / 8]) : ((~mask[(i) % 8]) & t[(i) / 8])
#define chr(i) (cs == sizeof(int)?((int*)s)[i]:((unsigned char*)s)[i])
#define isLMS(i) (i > 0 && tget(i) && !tget(i - 1))

// find the start or end of each bucket
void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
  int i, sum = 0;
  for (i = 0; i <= K; i++) bkt[i] = 0; // clear all buckets
  for (i = 0; i < n; i++) bkt[chr(i)]++; // compute the size of each bucket
  for (i = 0; i <= K; i++) {
    sum += bkt[i];
    bkt[i] = end ? sum : sum - bkt[i];
  }
}
// compute SAl
void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
  int i, j;
  getBuckets(s, bkt, n, K, cs, end);   // find starts of buckets
  for (i = 0; i < n; i++) {
    j = SA[i] - 1;
    if (j >= 0 && !tget(j)) SA[bkt[chr(j)]++] = j;
  }
}
// compute SAs
void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n, int K, int cs, bool end) {
  int i, j;
  getBuckets(s, bkt, n, K, cs, end);   // find ends of buckets
  for (i = n - 1; i >= 0; i--) {
    j = SA[i] - 1;
    if (j >= 0 && tget(j)) SA[--bkt[chr(j)]] = j;
  }
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n-1]=0 (the sentinel!), n>=2
// use a working space (excluding s and SA) of at most 2.25n+O(1) for a constant alphabet
void SA_IS(unsigned char *s, int *SA, int n, int K, int cs) {
  int i, j;
  unsigned char *t = (unsigned char*) malloc(n / 8 + 1);    // LS-type array in bits
  // Classify the type of each character
  tset(n - 2, 0);
  tset(n - 1, 1); // the sentinel must be in s1, important!!!
  for (i = n - 3; i >= 0; i--) tset(i, (chr(i) < chr(i + 1) || (chr(i) == chr(i + 1) && tget(i + 1) == 1))?1:0);
  // stage 1: reduce the problem by at least 1/2
  // sort all the S-substrings
  int *bkt = (int*) malloc(sizeof(int) * (K + 1));    // bucket array
  getBuckets(s, bkt, n, K, cs, true);   // find ends of buckets
  for (i = 0; i < n; i++) SA[i] = -1;
  for (i = 1; i < n; i++)
    if (isLMS(i)) SA[--bkt[chr(i)]] = i;
  induceSAl(t, SA, s, bkt, n, K, cs, false);
  induceSAs(t, SA, s, bkt, n, K, cs, true);
  free(bkt);
  // compact all the sorted substrings into the first n1 items of SA
  // 2*n1 must be not larger than n (proveable)
  int n1 = 0;
  for (i = 0; i < n; i++)
    if (isLMS(SA[i])) SA[n1++] = SA[i];
  // find the lexicographic names of all substrings
  for (i = n1; i < n; i++) SA[i] = -1; // init the name array buffer
  int name = 0, prev = -1;
  for (i = 0; i < n1; i++) {
    int pos = SA[i];
    bool diff = false;
    for (int d = 0; d < n; d++)
      if (prev == -1 || chr(pos + d) != chr(prev + d) || tget(pos + d) != tget(prev + d)) {
        diff = true;
        break;
      } else if (d > 0 && (isLMS(pos + d) || isLMS(prev + d))) break;
    if (diff) {
      name++;
      prev = pos;
    }
    pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
    SA[n1 + pos] = name - 1;
  }
  for (i = n - 1, j = n - 1; i >= n1; i--)
    if (SA[i] >= 0) SA[j--] = SA[i];
  // stage 2: solve the reduced problem
  // recurse if names are not yet unique
  int *SA1 = SA, *s1 = SA + n - n1;
  if (name < n1) SA_IS((unsigned char*) s1, SA1, n1, name - 1, sizeof(int));
  else
    // generate the suffix array of s1 directly
    for (i = 0; i < n1; i++) SA1[s1[i]] = i;
  // stage 3: induce the result for the original problem
  bkt = (int*) malloc(sizeof(int) * (K + 1));    // bucket array
  // put all left-most S characters into their buckets
  getBuckets(s, bkt, n, K, cs, true);   // find ends of buckets
  for (i = 1, j = 0; i < n; i++)
    if (isLMS(i)) s1[j++] = i; // get p1
  for (i = 0; i < n1; i++) SA1[i] = s1[SA1[i]]; // get index in s
  for (i = n1; i < n; i++) SA[i] = -1; // init SA[n1..n-1]
  for (i = n1 - 1; i >= 0; i--) {
    j = SA[i];
    SA[i] = -1;
    SA[--bkt[chr(j)]] = j;
  }
  induceSAl(t, SA, s, bkt, n, K, cs, false);
  induceSAs(t, SA, s, bkt, n, K, cs, true);
  free(bkt);
  free(t);
}

void calc_lcp(int n, unsigned char *s) {
  for (int i = 0; i < n; i++) rnk[sa[i]] = i;
  for (int i = 0, k = 0; i < n; i++) {
    if (rnk[i] == n - 1) {
      k = 0;
      lcp[n - 1] = 0;
      continue;
    }
    int j = sa[rnk[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[rnk[i]] = k;
    if (k) k--;
  }
}

void calc_sa(const string&str, bool with_lcp) {
  unsigned char *s = (unsigned char*) str.c_str();
  int n = str.size();
  SA_IS(s, sa, n + 1, 256, 1);
  for (int i = 1; i <= n; i++) sa[i - 1] = sa[i];
  if (with_lcp) calc_lcp(n, s);
}

void suffix_array() {
  calc_sa(x, true);

/*   iota(sa, sa + nx, 0);
   sort(sa, sa + nx, [&](int i, int j) {
    return x.substr(i) < x.substr(j);
   });

   lcp[0] = 0;
   for (int i = 1; i < nx; i++) {
    for (int i1 = sa[i - 1], i2 = sa[i]; i1 < nx and i2 < nx and x[i1] == x[i2]; i1++, i2++) {
      lcp[i]++;
    }
   } */
}

void reset() {
  for (int i = 0; i <= nx; i++) {
    q[i][0].clear();
    q[i][1].clear();
    sa[i] = lcp[i] = rnk[i] = 0;
  }
  for (int i = 1, en = (nx + 1) << 2; i <= en; i++) {
    tree[i] = lazy[i] = 0;
  }
  ans = 1;
}

inline void push(int u, int b, int e) {
  tree[u] += (long long)lazy[u] * (e - b + 1);
  if (b != e) lazy[u << 1] += lazy[u], lazy[u << 1 | 1] += lazy[u];
  lazy[u] = 0;
}
void update(int l, int r, int v, int u = 1, int b = 1, int e = nx + 1) {
  if (lazy[u]) push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    lazy[u] += v;
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
  tree[u] = tree[u << 1] + tree[u << 1 | 1];
}
long long query(int l, int r, int u = 1, int b = 1, int e = nx + 1) {
  if (b > r or e < l) return 0;
  if (lazy[u]) push(u, b, e);
  if (b >= l and e <= r) return tree[u];
  int mid = b + e >> 1;
  return query(l, r, u << 1, b, mid) +
         query(l, r, u << 1 | 1, mid + 1, e);
}

void zalgo(int id) {
  string ss = s[id] + x;
  int n = ss.size();

  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && ss[R - L] == ss[R]) R++;
      z[id][i] = R - L;
      R--;
    }
    else {
      int k = i - L;
      if (z[id][k] < R - i + 1) z[id][i] = z[id][k];
      else {
        L = i;
        while (R < n && ss[R - L] == ss[R]) R++;
        z[id][i] = R - L;
        R--;
      }
    }
  }

  for (int i = ns[id]; i < n; i++) {
    z[id][i - ns[id]] = min(z[id][i], ns[id]);
  }
  z[id][nx] = 0;
}

void test_case() {
  cin >> s[0] >> s[1] >> x;
  ns[0] = s[0].size();
  ns[1] = s[1].size();
  nx = x.size();

  zalgo(0);
  zalgo(1);

  suffix_array();

  // for (int i = 0; i < nx; i++) {
  //   debug(i, z[0][i], z[1][i], sa[i], lcp[i]);
  // }

  for (int i = 0; i < nx; i++) {
    int l = sa[i];
    int r = sa[i] + z[0][sa[i]];
    int u = min(sa[i] + lcp[i], nx);
    q[r][1].push_back(u);
    if (l > 0) q[l - 1][0].push_back(u);
  }

  for (int i = 0; i <= nx; i++) {
    int l = i, r = i + z[1][i];
    update(l + 1, r + 1, 1);

    for (int it = 0; it < 2; it++) {
      int e = it == 0 ? -1 : 1;
      for (int u : q[i][it]) {
        if (u < nx) {
          ans += 1ll * e * query(u + 2, nx + 1);
        }
      }
    }
  }

  cout << ans << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}