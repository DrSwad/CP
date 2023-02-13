#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> coal(n);
    for (int &i : coal) scanf("%d", &i);

    vector<int> tax(n - 1);
    for (int &i : tax) scanf("%d", &i);

    vector<int> policy(n - 1);
    for (int &i : policy) scanf("%d", &i);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int curr = 0;
      for (int j = 0; j <= i; j++) {
        curr += coal[j];
      }
      for (int j = 0; j < i; j++) {
        curr -= tax[j] * policy[j];
      }
      ans = max(ans, curr);
    }
    printf("%d\n", ans);
  }

  return 0;
}