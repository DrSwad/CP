#include <bits/stdc++.h>
using namespace std;

vector<int> convert(int num, int base) {
  vector<int> ret;
  while (num) {
    ret.push_back(num % base);
    num /= base;
  }
  return ret;
}

void answer(int a = -1, int b = -1) {
  if (a == -1 or b == -1) cout << "NO\n";
  else cout << "YES\n" << a << " " << b << "\n";
}

void test_case() {
  int x, y, A, B;
  cin >> x >> y >> A >> B;
  if (x == y) return answer(2, 2);

  map<vector<int>, int> mp_a;
  for (int a = 2; a <= A and a * a <= x; a++) {
    mp_a[convert(x, a)] = a;
  }
  for (int b = 2; b <= B and b * b <= y; b++) {
    if (mp_a.find(convert(y, b)) != mp_a.end()) {
      return answer(mp_a[convert(y, b)], b);
    }
  }

  vector<int> cs;
  for (int s = 1, d = abs(x - y); s * s <= d; s++) {
    if (d % s == 0) {
      cs.push_back(s);
      if (s * s != d) cs.push_back(d / s);
    }
  }

  for (int s : cs) {
    int a, b;
    if (x >= y) {
      int d = (x - y) / s;
      a = min(A, x / s);
      b = min(min(B, y / s), a - d);
      a = min(a, b + d);
    }
    else {
      int d = (y - x) / s;
      b = min(B, y / s);
      a = min(min(A, x / s), b - d);
      b = min(b, a + d);
    }
    if (2 <= a and a <= A and a > s and a > x - a * s and 2 <= b and b <= B and b > s and b > y - b * s) {
      return answer(a, b);
    }
  }

  answer();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}