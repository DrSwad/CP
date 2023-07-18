#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  int pos_count = 0, neg_count = 0;
  for (int i : a) {
    if (i >= 0) pos_count++;
    else neg_count++;
  }

  int sum = 0;
  vector<pair<int, int>> operations;

  if (pos_count == 0) {
    sum = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      operations.emplace_back(sum, a[i]);
      sum = sum - a[i];
    }
  }
  else if (neg_count == 0) {
    sum = a[0];
    for (int i = 1; i < n - 1; i++) {
      operations.emplace_back(sum, a[i]);
      sum = sum - a[i];
    }
    operations.emplace_back(a[n - 1], sum);
    sum = a[n - 1] - sum;
  }
  else {
    sum = a[0];
    for (int i = 1; i < n - 1; i++) {
      if (a[i] >= 0) {
        operations.emplace_back(sum, a[i]);
        sum = sum - a[i];
      }
    }
    operations.emplace_back(a[n - 1], sum);
    sum = a[n - 1] - sum;
    for (int i = 1; i < n - 1; i++) {
      if (a[i] < 0) {
        operations.emplace_back(sum, a[i]);
        sum = sum - a[i];
      }
    }
  }

  cout << sum << "\n";
  for (auto [add, sub] : operations) {
    cout << add << " " << sub << "\n";
  }

  return 0;
}