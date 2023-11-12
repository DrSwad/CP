#include <bits/stdc++.h>
using namespace std;

template<typename T, typename AssociativeOperation>
struct segment_tree {
  int SZ;
  T identity;
  AssociativeOperation TT;
  std::vector<T> data;

  segment_tree() {}

  segment_tree(int _SZ, T _identity, AssociativeOperation _TT)
    : SZ(_SZ), identity(_identity), TT(_TT) {
    data.resize(2 * SZ, identity);
  }

  // Returns the value at index i
  const T& operator[](int i) const {
    assert(0 <= i && i < SZ);
    return data[SZ + i];
  }

  // Assigns fn(i) at index i for each i in [0, SZ)
  template<typename Function>
  void assign(Function fn) {
    for (int i = 0; i < SZ; i++) data[SZ + i] = fn(i);
    for (int i = SZ - 1; i; i--) data[i] = TT(data[2 * i], data[2 * i + 1]);
  }

  // Assigns v at index i
  void assign(int i, T v) {
    assert(0 <= i && i < SZ);
    data[i += SZ] = v;
    for (i /= 2; i; i /= 2) data[i] = TT(data[2 * i], data[2 * i + 1]);
  }

  // Returns the result of a left fold of the elements at indices in [first, last) over TT
  T accumulate(int first, int last) const {
    assert(0 <= first && last <= SZ);
    T left = identity, right = identity;
    for (first += SZ, last += SZ; first < last; first /= 2, last /= 2) {
      if (first & 1) left  = TT(left, data[first++]);
      if (last  & 1) right = TT(data[--last], right);
    }
    return TT(left, right);
  }
};

const int A = 1e6 + 5;
vector<int> prime;
bool is_composite[A];
int min_divisor[A];

void find_min_divisors() {
  min_divisor[1] = 1;
  for (int i = 2; i < A; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      min_divisor[i] = i;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < A; j++) {
      is_composite[i * prime[j]] = true;
      min_divisor[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}

int tot_divisors;
int divisors[A];

void find_divisors(int num) {
  if (num == 1) return;

  int p = min_divisor[num];
  int pp = p;
  int prv_tot_divisors = tot_divisors;

  while (num % p == 0) {
    for (int i = 1; i <= prv_tot_divisors; i++) {
      divisors[++tot_divisors] = pp * divisors[i];
    }
    num /= p;
    pp *= p;
  }

  find_divisors(num);
}

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  segment_tree st_gcd(n, 0, [&](int i, int j) { return gcd(i, j); });
  st_gcd.assign([&](int i) { return a[i] - b[i]; });

  segment_tree st_diff_min(n, INT_MAX, [&](int i, int j) { return min(i, j); });
  st_diff_min.assign([&](int i) { return a[i] - b[i]; });

  segment_tree st_b_max(n, 0, [&](int i, int j) { return max(i, j); });
  st_b_max.assign([&](int i) { return b[i]; });

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;

    if (st_diff_min.accumulate(l, r) < 0) cout << "-1\n";
    else {
      int g = st_gcd.accumulate(l, r);
      int max_b = st_b_max.accumulate(l, r);
      if (g == 0) cout << max_b + 1 << "\n";
      else if (g <= max_b) cout << "-1\n";
      else {
        tot_divisors = 1;
        divisors[1] = 1;
        find_divisors(g);

        int ans = g;
        for (int i = 1; i <= tot_divisors; i++) {
          if (divisors[i] > max_b) {
            ans = min(ans, divisors[i]);
          }
        }
        cout << ans << "\n";
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  find_min_divisors();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}