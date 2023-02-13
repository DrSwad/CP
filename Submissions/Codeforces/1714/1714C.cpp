#include <bits/stdc++.h>
using namespace std;

bool is_possible(int s, int d) {
  int mx_s = 0;
  for (int i = 0; i < d; i++) {
    mx_s += 9 - i;
  }
  return mx_s >= s;
}

void construct(int s, int d) {
  vector<int> v;
  int curr_s = 0;
  for (int i = 0; i < d; i++) {
    v.push_back(9 - i);
    curr_s += 9 - i;
  }
  reverse(v.begin(), v.end());

  for (int i = 0; i < d; i++) {
    while (curr_s > s and v[i] > i + 1) {
      curr_s--, v[i]--;
    }
  }

  for (int i : v) cout << i;
  cout << "\n";
}

void test_case() {
  int s;
  cin >> s;

  int d;
  for (d = 1; d <= 8; d++) {
    if (is_possible(s, d)) break;
  }

  construct(s, d);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}