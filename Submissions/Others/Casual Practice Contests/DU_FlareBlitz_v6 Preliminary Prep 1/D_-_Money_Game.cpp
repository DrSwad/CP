#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long sum = 0;
  for (int i : a) sum += i;
  long long down = n + 1;

  cout << fixed << setprecision(10);
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    long long up = i == 0 ? 2 : 1;
    cout << (long double)up * sum / down;
  }
  cout << "\n";

  return 0;
}