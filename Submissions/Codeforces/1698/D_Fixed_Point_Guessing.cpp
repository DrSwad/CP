#include <bits/stdc++.h>
using namespace std;

vector<int> query(int l, int r) {
  cout << "? " << l << " " << r << endl;
  vector<int> res;
  for (int i = 0; i < r - l + 1; i++) {
    int x;
    cin >> x;
    res.push_back(x);
  }
  return res;
}

void answer(int ans) {
  cout << "! " << ans << endl;
}

bool is_in_subarray(int l, int r) {
  vector<int> res = query(l, r);
  int cnt = 0;
  for (int i : res) {
    cnt += i < l or r < i;
  }

  int len = r - l + 1;
  int rem = len - cnt;
  return rem % 2 == 1;
}

void test_case() {
  int n;
  cin >> n;

  int l = 1, r = n;
  while (l != r) {
    int m = (l + r) / 2;
    if (is_in_subarray(l, m)) r = m;
    else l = m + 1;
  }

  answer(l);
}

int main() {

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}