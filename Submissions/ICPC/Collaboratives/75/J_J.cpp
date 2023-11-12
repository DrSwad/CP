#include <bits/stdc++.h>
using namespace std;

const int len = 1e9;

// int remaining_queries = 30;

int query(int from) {
  // assert(remaining_queries >= 1), remaining_queries--;
  int to = (from + len / 2 - 1) % len;
  cout << "QUERY " << from << " " << to << endl << flush;
  int res;
  cin >> res;
  return res;
}

void answer(int ans) {
  // assert(remaining_queries >= 1), remaining_queries--;
  cout << "YES " << ans << endl << flush;
  exit(EXIT_SUCCESS);
}

int main() {
  int n;
  cin >> n;
  // assert(n % 2 == 0);
  // remaining_queries += int(log2(sqrt(n)));

  int res0 = query(0);
  if (res0 == n / 2) answer(0);

  int L = 0, R = len / 2;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    int res = query(mid);
    if (res == n / 2) answer(mid);
    else if ((res > n / 2) == (res0 > n / 2)) L = mid;
    else R = mid;
  }

  // assert(false);

  return 0;
}