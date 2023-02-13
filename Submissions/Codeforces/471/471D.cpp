#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> prefix_function(int n, const T &s) {
  vector<int> p(n, 0);
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && !(s[i] == s[k])) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    p[i] = k;
  }
  return p;
}
template<typename T>
vector<int> prefix_function(const T &s) {
  return prefix_function((int) s.size(), s);
}

// Returns 0-indexed positions of occurrences of s in w
template<typename T>
vector<int> kmp_search(int n, const T &s, int m, const T &w, const vector<int> &p) {
  assert(n >= 1 && (int) p.size() == n);
  vector<int> res;
  int k = 0;
  for (int i = 0; i < m; i++) {
    while (k > 0 && (k == n || !(w[i] == s[k]))) {
      k = p[k - 1];
    }
    if (w[i] == s[k]) {
      k++;
    }
    if (k == n) {
      res.push_back(i - n + 1);
    }
  }
  return res;
}
template<typename T>
vector<int> kmp_search(const T &s, const T &w, const vector<int> &p) {
  return kmp_search((int) s.size(), s, (int) w.size(), w, p);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, w;
  cin >> n >> w;

  vector<int> a(n), b(w);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  if (w == 1) {
    cout << n << "\n";
  }
  else if (n == 1) {
    cout << "0\n";
  }
  else {
    vector<int> da(n - 1);
    for (int i = 0; i < n - 1; i++) {
      da[i] = a[i + 1] - a[i];
    }

    vector<int> db(w - 1);
    for (int i = 0; i < w - 1; i++) {
      db[i] = b[i + 1] - b[i];
    }

    cout << kmp_search(db, da, prefix_function(db)).size() << "\n";
  }

  return 0;
}