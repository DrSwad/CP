#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long sum = 0;
  for (int i : a) sum += i;

  if ((2 * sum) % n != 0) {
    cout << "0\n";
    return;
  }

  long long T = 2 * sum / n;
  map<int, int> f;
  for (int i : a) f[i]++;

  long long ans = 0;
  for (int i : a) {
    if (i > T) continue;
    int j = T - i;
    if (f.find(j) != f.end()) {
      ans += f[j] - (i == j);
    }
  }

  cout << ans / 2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}