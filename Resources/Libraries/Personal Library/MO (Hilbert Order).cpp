constexpr int logn = 20;
constexpr int maxn = 1 << logn;
ll hilbertOrder(int x, int y) {
  ll d = 0;
  for (int s = 1 << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    d = d << 2 | rx * 3 ^ static_cast<int>(ry);
    if (!ry) {
      if (rx) {
        x = maxn - x;
        y = maxn - y;
      }
      swap(x, y);
    }
  }
  return d;
}