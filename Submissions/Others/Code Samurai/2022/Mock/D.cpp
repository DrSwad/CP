#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<int, int> vis;
  long long sum = 0;

  while (n--) {
    long long a;
    cin >> a;
    long long abs_a = a >= 0 ? a : -a;

    sum -= vis[abs_a];
    vis[abs_a] = a;
    sum += a;
  }

  cout << sum << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}