#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> x(n);
  for (int &i : x) cin >> i, i--;

  int nn = n * n;
  vector<int> a(nn, -1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      return x[i] < x[j];
    }
  );

  queue<int> q;
  for (int i : order) {
    a[x[i]] = i;
    for (int j = 0; j < i; j++) {
      q.push(i);
    }
  }
  for (int i : order) {
    for (int j = i + 1; j < n; j++) {
      q.push(i);
    }
  }

  for (int i = 0; i < nn; i++) {
    if (a[i] != -1) continue;
    assert(!q.empty());
    a[i] = q.front();
    q.pop();
  }
  assert(q.empty());

  vector<int> cnt(n, 0);
  for (int i = 0; i < nn; i++) {
    cnt[a[i]]++;
    if (cnt[a[i]] == a[i] + 1) {
      if (i != x[a[i]]) {
        cout << "No\n";
        return 0;
      }
    }
  }

  cout << "Yes\n";
  for (int i = 0; i < nn; i++) {
    if (i) cout << " ";
    cout << a[i] + 1;
  }
  cout << "\n";

  return 0;
}