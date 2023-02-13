#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  if (n == 1) {
    cout << "-1\n";
    return;
  }

  vector<int> q(n);

  if (n == 2) {
    q[0] = 1, q[1] = 2;
    if (p[0] == q[0]) {
      swap(q[0], q[1]);
    }
  }
  else {
    int i;
    for (i = 0; i < n - 3; ) {
      if (p[i] != i + 1) {
        q[i] = i + 1;
        i++;
      }
      else {
        q[i] = i + 2;
        q[i + 1] = i + 1;
        i += 2;
      }
    }

    if (p[i] != i + 1) q[i] = i + 1, i++;
    if (n - i == 2) {
      q[i] = i + 1;
      q[i + 1] = i + 2;
      if (p[i] == q[i] or p[i + 1] == q[i + 1]) {
        swap(q[i], q[i + 1]);
      }
    }
    else {
      q[i] = i + 2;

      q[i + 1] = i + 1;
      q[i + 2] = i + 3;
      if (p[i + 1] == q[i + 1] or p[i + 2] == q[i + 2]) {
        swap(q[i + 1], q[i + 2]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << q[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}