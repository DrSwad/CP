template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  BIT(const vector<T> &a) { // O(n)
    n = a.size();
    f.assign(n + 1, (T)0);
    for (int i = 1; i <= n; i++) {
      f[i] += a[i - 1];
      if (i + (i & -i) <= n) {
        f[i + (i & -i)] += f[i];
      }
    }
  }
  void update(int p, T v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};