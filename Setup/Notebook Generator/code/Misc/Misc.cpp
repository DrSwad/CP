// Pragmas
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3,unroll-loops") 
#pragma GCC target("avx,avx2,fma")

// Custom Priority Queue
std::priority_queue< int, std::vector<int>, std::greater<int> > Q; // increasing

//gp hash table https://codeforces.com/blog/entry/60737
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<key, int, chash> table;

//bitset
BS._Find_first()
BS._Find_next(x) //Return first set bit after xth bit, x on failure

//Gray Code, G(0) = 000, G(1) = 001, G(2) = 011, G(3) = 010
inline int g(int n){ return n ^ (n >> 1); }

//Inverse Gray Code
int rev_g(int g) {
  int n = 0;
  for (; g; g >>= 1) n ^= g;
  return n;
}

/// Only for non-negative integers
/// Returns the immediate next number with same count of one bits, -1 on failure
long long hakmemItem175(long long n){
  if(!n) return -1;
  long long x = (n & -n);
  long long left = (x + n);
  long long right = ((n ^ left) / x) >> 2;
  long long res = (left | right);
  return res;
}

/// Returns the immediate previous number with same count of one bits, -1 on failure
long long lol(long long n){
  if(n < 2) return -1;
  long long res = ~hakmemItem175(~n);
  return (!res) ? -1 : res;
}

//Gilbert Ordering for Mo's Algorithm
inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) {
    return 0;
  }
  int hpow = 1 << (pow-1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : 
            ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2*pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}
 
struct Query {
  int l, r, idx; // queries
  int64_t ord; // Gilbert order of a query
  // call query[i].calcOrder() to calculate the Gilbert orders
  inline void calcOrder() {
    ord = gilbertOrder(l, r, 21, 0);
  }
};
// sort the queries based on the Gilbert order
inline bool operator<(const Query &a, const Query &b) {
  return a.ord < b.ord;
}