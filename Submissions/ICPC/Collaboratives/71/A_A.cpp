#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int day = 0;
  int rem = m;
  while (n >= 1) {
    n--;
    rem--;
    day++;
    if (rem == 0) {
      n++;
      rem = m;
    }
  }

  cout << day << "\n";

  return 0;
}