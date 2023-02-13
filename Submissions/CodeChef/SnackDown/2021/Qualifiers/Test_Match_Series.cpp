#include <bits/stdc++.h>
using namespace std;

void test_case() {
  vector<int> cnt(3, 0);
  for (int i = 0; i < 5; i++) {
    int r;
    cin >> r;
    cnt[r]++;
  }

  cout << (cnt[1] > cnt[2] ? "INDIA" : cnt[1] < cnt[2] ? "ENGLAND" : "DRAW") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}