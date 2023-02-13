#include <bits/stdc++.h>
using namespace std;

int query(vector<int> a) {
  cout << "?";
  for (int i : a) cout << " " << i;
  cout << endl;

  int x;
  cin >> x;
  return x;
}

void answer(int x) {
  cout << x << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, k;
  cin >> n >> k;

  return 0;
}