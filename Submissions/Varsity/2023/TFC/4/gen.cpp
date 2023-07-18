#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

string get_random_string(int len) {
  string s;
  while (len--) {
    s += 'a' + get_random(0, 25);
  }
  return s;
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int L = 8;
  const int N = 5;
  const int Q = 5;

  int n = get_random(1, N);
  int q = get_random(1, Q);
  cout << q << " " << n << "\n";

  function<string(string, int)> change =
    [&](string s, int d) {
      while (d--) {
        int i = get_random(0, L - 1);
        s[i] = get_random_string(1)[0];
      }
      return s;
    };

  string s = get_random_string(L);
  while (n--) {
    string ns = change(s, get_random(0, 3));
    cout << ns << "\n";
  }
  while (q--) {
    string qs = change(s, get_random(0, 3));
    int d = get_random(0, 2);
    cout << qs << " " << d << "\n";
  }

  return 0;
}