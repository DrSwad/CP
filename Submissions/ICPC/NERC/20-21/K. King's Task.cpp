#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 5000;

void go(vector<int> &v, int type) {
  if (type == 0) {
    for (int i = 0; i < v.size(); i += 2) {
      swap(v[i], v[i + 1]);
    }
  } else {
    int n = v.size() / 2;
    for (int i = 0; i < n; i++) {
      swap(v[i], v[i + n]);
    }
  }
}

int main() {
  int n;
  cin >> n;

  vector<int> p(2 * n);
  for (int &i : p) scanf("%d", &i);

  int ans = 0;
  vector<int> a = p, b = p;
  for (int i = 0; i < MAGIC; i++) {
    if (is_sorted(a.begin(), a.end())) break;
    if (is_sorted(b.begin(), b.end())) break;
    ans++;
    go(a, i % 2 == 1);
    go(b, i % 2 == 0);
  }

  cout << (ans < MAGIC ? ans : -1) << endl;

  return 0;
}