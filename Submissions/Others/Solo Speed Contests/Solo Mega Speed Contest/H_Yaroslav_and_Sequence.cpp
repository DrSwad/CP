#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(2 * n - 1);
  for (int &i : a) scanf("%d", &i);

  int sum = 0, neg = 0;
  for (int &i : a) {
    neg += i < 0;
    i = abs(i);
    sum += i;
  }

  if (n % 2 == 1 or neg % 2 == 0) cout << sum << endl;
  else cout << sum - 2 * *min_element(a.begin(), a.end()) << endl;

  return 0;
}