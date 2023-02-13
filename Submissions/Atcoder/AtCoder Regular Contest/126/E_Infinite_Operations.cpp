#include <bits/stdc++.h>
using namespace std;

template<typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template<typename T>
class Modular {
public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template<typename U>
  Modular(const U&x) {
    value = normalize(x);
  }

  template<typename U>
  static Type normalize(const U&x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type&operator()() const { return value; }
  template<typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular&operator+=(const Modular&other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular&operator-=(const Modular&other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template<typename U> Modular&operator+=(const U&other) { return *this += Modular(other); }
  template<typename U> Modular&operator-=(const U&other) { return *this -= Modular(other); }
  Modular&operator++() { return *this += 1; }
  Modular&operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template<typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type&operator*=(const Modular&rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm (
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
      );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template<typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type&operator*=(const Modular&rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template<typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type&operator*=(const Modular&rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular&operator/=(const Modular&other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type&abs(const Modular&x) { return x.value; }

  template<typename U>
  friend bool operator==(const Modular<U>&lhs, const Modular<U>&rhs);

  template<typename U>
  friend bool operator<(const Modular<U>&lhs, const Modular<U>&rhs);

  template<typename V, typename U>
  friend V&operator>>(V&stream, Modular<U>&number);

private:
  Type value;
};

template<typename T> bool operator==(const Modular<T>&lhs, const Modular<T>&rhs) { return lhs.value == rhs.value; }
template<typename T, typename U> bool operator==(const Modular<T>&lhs, U rhs) { return lhs == Modular<T>(rhs); }
template<typename T, typename U> bool operator==(U lhs, const Modular<T>&rhs) { return Modular<T>(lhs) == rhs; }

template<typename T> bool operator!=(const Modular<T>&lhs, const Modular<T>&rhs) { return !(lhs == rhs); }
template<typename T, typename U> bool operator!=(const Modular<T>&lhs, U rhs) { return !(lhs == rhs); }
template<typename T, typename U> bool operator!=(U lhs, const Modular<T>&rhs) { return !(lhs == rhs); }

template<typename T> bool operator<(const Modular<T>&lhs, const Modular<T>&rhs) { return lhs.value < rhs.value; }

template<typename T> Modular<T> operator+(const Modular<T>&lhs, const Modular<T>&rhs) { return Modular<T>(lhs) += rhs; }
template<typename T, typename U> Modular<T> operator+(const Modular<T>&lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template<typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>&rhs) { return Modular<T>(lhs) += rhs; }

template<typename T> Modular<T> operator-(const Modular<T>&lhs, const Modular<T>&rhs) { return Modular<T>(lhs) -= rhs; }
template<typename T, typename U> Modular<T> operator-(const Modular<T>&lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template<typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>&rhs) { return Modular<T>(lhs) -= rhs; }

template<typename T> Modular<T> operator*(const Modular<T>&lhs, const Modular<T>&rhs) { return Modular<T>(lhs) *= rhs; }
template<typename T, typename U> Modular<T> operator*(const Modular<T>&lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template<typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>&rhs) { return Modular<T>(lhs) *= rhs; }

template<typename T> Modular<T> operator/(const Modular<T>&lhs, const Modular<T>&rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U> Modular<T> operator/(const Modular<T>&lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>&rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>&a, const U&b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template<typename T>
bool IsZero(const Modular<T>&number) {
  return number() == 0;
}

template<typename T>
string to_string(const Modular<T>&number) {
  return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template<typename U, typename T>
U&operator<<(U&stream, const Modular<T>&number) {
  return stream << number();
}

// U == std::istream? but done this way because of fastinput
template<typename U, typename T>
U&operator>>(U&stream, Modular<T>&number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
   using ModType = int;

   struct VarMod { static ModType value; };
   ModType VarMod::value;
   ModType& md = VarMod::value;
   using Mint = Modular<VarMod>;
 */

constexpr int md = (int)998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

/*vector<Mint> fact(1, 1);
   vector<Mint> inv_fact(1, 1);

   Mint C(int n, int k) {
   if (k < 0 || k > n) {
    return 0;
   }
   while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
   }
   return fact[n] * inv_fact[k] * inv_fact[n - k];
   }*/

template<typename T, class F = function<T(const T&, const T&)>>
class SegmentTree {
  int n;
  vector<T> a;
  vector<T> st;
  T st_default;
  F merge;
  F setval;
  void build(int stI, int L, int R) {
    if (L == R) {
      st[stI] = a[L - 1];
      return;
    }

    int mid = (L + R) >> 1;
    build(stI << 1, L, mid);
    build(stI << 1 | 1, mid + 1, R);

    st[stI] = merge(st[stI << 1], st[stI << 1 | 1]);
  }
  void update(int stI, int L, int R, int at, T val) {
    if (L == R) {
      st[stI] = setval(st[stI], val);
      return;
    }

    int mid = (L + R) >> 1;
    if (at <= mid) update(stI << 1, L, mid, at, val);
    else update(stI << 1 | 1, mid + 1, R, at, val);

    st[stI] = merge(st[(stI << 1)], st[(stI << 1) + 1]);
  }
  T query(int stI, int L, int R, int l, int r) {
    if (l <= L && R <= r) return st[stI];

    int mid = (L + R) >> 1;
    if (r <= mid) return query(stI << 1, L, mid, l, r);
    else if (mid + 1 <= l) return query(stI << 1 | 1, mid + 1, R, l, r);
    else return merge(
        query(stI << 1, L, mid, l, mid),
        query(stI << 1 | 1, mid + 1, R, mid + 1, r)
        );
  }
public:
  SegmentTree(const vector<T> &_a, const F &_merge, const F &_setval, T st_default, bool build_init) {
    n = static_cast<int>(_a.size());
    a = _a;
    st.resize(4 * n + 1, st_default);
    this->st_default = st_default;
    merge = _merge;
    setval = _setval;
    if (build_init) build(1, 1, n);
  }
  T query(int l, int r) { // range [l, r], 1-based index
    if (r < 1 || n < l || r < l) return st_default;
    l = max(l, 1); r = min(r, n);
    return query(1, 1, n, l, r);
  }
  void update(int at, T val) { // at is 1-based index
    if (at < 1 || n < at) return;
    update(1, 1, n, at, val);
  }
};
// SegmentTree<long long> st(a, [&](long long i, long long j) {return i + j;}, [&](long long i, long long j) {return j;}, 0ll, true)

const int N = 3e5 + 5;

int n, q;
int a[N];
int x[N], y[N];
vector<int> cmp;
Mint stair_sum;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cmp.push_back(a[i]);
  }

  for (int i = 1; i <= q; i++) {
    cin >> x[i] >> y[i];
    cmp.push_back(y[i]);
  }

  sort(cmp.begin(), cmp.end());
  cmp.resize(unique(cmp.begin(), cmp.end()) - cmp.begin());
  int nn = cmp.size();

  vector<int> freq(nn, 0);
  for (int i = 1; i <= n; i++) {
    int at = lower_bound(cmp.begin(), cmp.end(), a[i]) - cmp.begin();
    freq[at]++;
  }

  vector<Mint> nums(nn, 0);
  for (int i = 0, cnt = 0; i < nn; i++) {
    nums[i] += (long long)cmp[i] * freq[i];
    for (int j = 0; j < freq[i]; j++) {
      cnt++;
      stair_sum += (long long)cmp[i] * cnt;
    }
  }

  SegmentTree<int> ft(freq, [&](int i, int j) {return i + j;}, [&](int i, int j) {return i + j;}, 0, true);
  SegmentTree<Mint> st(nums, [&](Mint i, Mint j) {return i + j;}, [&](Mint i, Mint j) {return i + j;}, 0, true);

  for (int qq = 1; qq <= q; qq++) {
    int xx = x[qq];
    int yy = y[qq];
    int pa = a[xx];
    a[xx] = yy;
    int na = a[xx];

    int at = lower_bound(cmp.begin(), cmp.end(), pa) - cmp.begin();
    stair_sum -= st.query(at + 1, nn);
    st.update(at + 1, -pa);
    stair_sum -= (long long)pa * ft.query(1, at);
    ft.update(at + 1, -1);

    at = lower_bound(cmp.begin(), cmp.end(), na) - cmp.begin();
    ft.update(at + 1, 1);
    stair_sum += (long long)na * ft.query(1, at);
    st.update(at + 1, na);
    stair_sum += st.query(at + 1, nn);

    Mint ans = stair_sum - st.query(1, nn) * (n + 1) / 2;
    cout << ans << "\n";
  }

  return 0;
}