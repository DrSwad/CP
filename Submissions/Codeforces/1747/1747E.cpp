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

const int N = 2e6 + 5;
const int INV2 = (md + 1) / 2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<vector<vector<Mint>>> dp(2);

  dp[0] = {
    {1, 1, 2},
    {1, 3, 8},
    {2, 8, 26},
  };
  dp[1] = {
    {0, 1, 3},
    {1, 5, 18},
    {3, 18, 75},
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 3; j < N; j++) {
      for (int id = 0; id < 2; id++) {
        dp[id][i].push_back(0);
        if (i >= 1) dp[id][i][j] += 2 * dp[id][i - 1][j];
        if (j >= 1) dp[id][i][j] += 2 * dp[id][i][j - 1];
        if (i >= 1 and j >= 1) dp[id][i][j] -= 2 * dp[id][i - 1][j - 1];
        if (id == 1) dp[id][i][j] += dp[id ^ 1][i][j] * INV2;
      }
    }
  }

  auto diagonal_sum = [&](int id, int col, int len) {
    vector<vector<Mint>> diag_sum(2, vector<Mint>(max(len + 1, 3)));
    for (int id = 0; id < 2; id++) {
      for (int i = 0; i < 3; i++) {
        for (int j = col; j < col + 3 and i + j <= col + 2; j++) {
          diag_sum[id][i + j - col] += dp[id][i][j];
        }
      }
    }

    debug(diag_sum);

    for (int i = 3; i <= len; i++) {
      diag_sum[0][i] = 4 * diag_sum[0][i - 1] - 2 * diag_sum[0][i - 2];
      diag_sum[1][i] = 4 * diag_sum[1][i - 1] - 2 * diag_sum[1][i - 2] + diag_sum[0][i] * INV2;
    }

    return diag_sum[id][len];
  };

  int t;
  cin >> t;

  cerr << diagonal_sum(0, 1, 3) << endl;

  // while (t--) {
  //   int n, m;
  //   cin >> n >> m;
  //   debug(n, m);

  //   int sum1 = diagonal_sum(1, 0, n + m);
  //   sum1 -= diagonal_sum(1, n + 1, m - 1);
  //   sum1 -= diagonal_sum(1, m + 1, n - 1);
  //   int sum2 = diagonal_sum(0, 0, n + m);
  //   debug(sum2);
  //   sum2 -= diagonal_sum(0, n + 1, m - 1);
  //   debug(sum2);
  //   sum2 -= diagonal_sum(0, m + 1, n - 1);
  //   debug(sum2);
  //   cout << sum1 + sum2 << "\n";
  // }

  return 0;
}