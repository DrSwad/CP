#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  int s = 1000;
  int n = 4;
  int mx = 1e9;

  cout << s << " " << n << endl;

  vector<pair<long long, long long>> p(n);
  auto signed_area = [&](int i, int j, int k) {
    return (p[i].x * p[j].y + p[j].x * p[k].y + p[k].x * p[i].y) -
           (p[i].y * p[j].x + p[j].y * p[k].x + p[k].y * p[i].x);
  };

  for (int i = 0; i < n; i++) {
    long long x = rnd.next(mx);
    long long y = rnd.next(mx);
    if (find(p.begin(), p.end(), make_pair(x, y)) != p.end()) {
      i--;
      continue;
    }

    p[i] = make_pair(x, y);
    bool flag = true;
    for (int j = 0; j < i; j++) {
      for (int k = j + 1; k < i; k++) {
        if (signed_area(i, j, k) == 0) {
          flag = false;
        }
      }
    }
    if (flag) {
      cout << x << " " << y << endl;
    }
    else i--;
  }

  return 0;
}