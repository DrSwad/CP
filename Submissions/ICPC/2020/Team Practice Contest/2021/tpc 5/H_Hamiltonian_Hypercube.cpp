#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 61;

ll dist(int n, ll code) {
  if (n == 1) return code;

  ll cdist = dist(n - 1, code & (1ll << (n - 1)) - 1);
  bool msb = code >> (n - 1);

  if (!msb) return cdist;
  else return (1ll << n) - 1 - cdist;
}

int main() {
  int n;
  ll a, b;
  string A, B;
  cin >> n >> A >> B;
  a = bitset<N>(A).to_ullong();
  b = bitset<N>(B).to_ullong();

  cout << dist(n, b) - dist(n, a) - 1 << endl;

  return 0;
}