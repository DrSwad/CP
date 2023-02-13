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

constexpr int md = (int) 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

const int C = 21;
const int N = 8e5 + 5;

int n;
tuple<int, int, int> e[N];
vector<int> adj[N];
int sub[C][N][2];
Mint total[C];

void reset() {
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
  }
  for (int c = 1; c < C; c++) {
    total[c] = 0;

    for (int i = 1; i <= n; i++) {
      sub[c][i][0] = sub[c][i][1] = 0;
    }
  }
}

void dfs1(int at, int pE, int minW) {
  sub[minW][pE][1] = 1;

  for (int cE : adj[at]) {
    if (cE != pE) {
      auto [v1, v2, w] = e[cE];
      int to = v1 ^ v2 ^ at;
      dfs1(to, cE, minW);
      long long res = sub[minW][cE][1];

      if (w >= minW) sub[minW][pE][1] += res;
      else total[minW] += res * (res - 1) / 2;
    }
  }
}

void dfs2(int at, int pE, int minW) {
  auto [pv1, pv2, pw] = e[pE];

  for (int cE : adj[at]) {
    if (cE != pE) {
      auto [cv1, cv2, cw] = e[cE];

      sub[minW][cE][0] = sub[minW][pE][1];
      if (pw >= minW) sub[minW][cE][0] += sub[minW][pE][0];
      if (cw >= minW) sub[minW][cE][0] -= sub[minW][cE][1];

      int to = cv1 ^ cv2 ^ at;
      dfs2(to, cE, minW);
    }
  }
}

void test_case() {
  cin >> n;

  e[0] = make_tuple(0, 1, 0);

  for (int i = 1; i <= n - 1; i++) {
    int from, to, w;
    cin >> from >> to >> w;

    e[i] = make_tuple(from, to, w);
    adj[from].push_back(i);
    adj[to].push_back(i);
  }

  for (int c = 1; c < C; c++) {
    dfs1(1, 0, c);
    long long res = sub[c][0][1];
    total[c] += res * (res - 1) / 2;
    dfs2(1, 0, c);
  }

  for (int c = 1; c < C; c++) {
    if (c < C - 1) total[c] -= total[c + 1];
    total[c] *= c;
  }

  Mint ans = 1;

  for (int ei = 1; ei < n; ei++) {
    Mint S = 0;

    for (int c = 1; c < C; c++) {
      S += total[c];
    }

    auto [v1, v2, w] = e[ei];

    for (int c = 1; c <= w; c++) {
      Mint freq = (long long)sub[c][ei][0] * sub[c][ei][1];
      if (c < w) freq -= (long long)sub[c + 1][ei][0] * sub[c + 1][ei][1];
      S -= freq * c;
    }

    ans *= S;
  }

  cout << ans << "\n";

  reset();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}