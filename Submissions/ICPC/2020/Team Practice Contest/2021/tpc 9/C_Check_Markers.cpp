#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  scanf("%d", &n);

  vector<int> a(n), b(n);
  for (int &i : a) scanf("%d", &i);
  for (int &i : b) scanf("%d", &i);

  long long A = 0, B = 0;
  for (int i : a) A += i;
  for (int i : b) B += i;

  map<int, int> ab;
  for (int i = 0; i < n; i++) ab[a[i] + b[i]]++;

  bool possible = false;
  for (int i = 0; i < n; i++) {
    int sum = a[i] + b[i];
    ab[sum]--;
    if (!ab[sum]) ab.erase(sum);
    B -= b[i];

    if (ab.rbegin()->first <= A and B <= A) {
      possible = true;
      break;
    }

    ab[sum]++;
    B += b[i];
  }

  puts(possible ? "YES" : "NO");
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}