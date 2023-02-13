template<unsigned int D>
class XorBasis {
  // typedef conditional<D <= 32, unsigned int, unsigned long long>::type T;
  typedef unsigned long long T;
public:
  vector<T> basis;
  XorBasis(T v = 0) {
    basis.resize(D, 0);
    insert(v);
  }
  void insert(T v) {
    for (int i = 0; i < D and v; i++) {
      if (!(v >> i & 1)) continue;
      if (!basis[i]) { basis[i] = v; break; }
      v ^= basis[i];
    }
  }
  bool query(T v) {
    for (int i = 0; i < D and v; i++) {
      if (!(v >> i & 1)) continue;
      if (!basis[i]) return false;
      v ^= basis[i];
    }
    return true;
  }
};