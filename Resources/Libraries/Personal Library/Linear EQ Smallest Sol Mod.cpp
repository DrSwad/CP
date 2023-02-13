// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
pair<long long, long long> inv_gcd(long long a, long long b) {
  a %= b;
  if (a < 0) a += b;
  if (a == 0) return {b, 0};

  long long s = b, t = a;
  long long m0 = 0, m1 = 1;

  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;

    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }

  if (m0 < 0) m0 += b / s;
  return {s, m0};
}

// @param m `1 <= m`
// @return x s.t. xa = r (mod m), 0 <= x < m/gcd(a, m)
long long smallest_solution(long long a, long long r, long long m) {
  r %= m;
  if (r < 0) r += m;

  auto [g, x] = inv_gcd(a, m);
  assert(r % g == 0);

  // return x * (r / g) % m; // use this if m <= INT_MAX
  return (long long)((__int128)x * (r / g) % m);
}