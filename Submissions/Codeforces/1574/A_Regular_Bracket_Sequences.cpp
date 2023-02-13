#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) cout << "(";
    for (int j = 0; j < i; j++) cout << ")";
    int k = n - i;
    for (int j = 0; j < k; j++) cout << "(";
    for (int j = 0; j < k; j++) cout << ")";
    cout << "\n";
  }
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