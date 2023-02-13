#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, total_minutes, speed1, speed2;
  cin >> n >> m >> total_minutes >> speed1 >> speed2;

  int pos1 = 1, pos2 = 1;
  int rem_minutes = total_minutes;
  int cycle_length = n - m + 1;
  int met = 0;

  while (rem_minutes > 0) {
    pos1 += speed1;
    if (pos1 >= m) pos1 = m + (pos1 - m) % cycle_length;
    pos2 += speed2;
    if (pos2 >= m) pos2 = m + (pos2 - m) % cycle_length;
    met += pos1 == pos2;
    rem_minutes--;
  }

  cout << met << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}