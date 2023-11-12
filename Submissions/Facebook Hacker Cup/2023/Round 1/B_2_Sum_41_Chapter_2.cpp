#include <bits/stdc++.h>
using namespace std;

vector<int> min_ans;
vector<int> cur_ans;

void go(int sum, int prod) {
  if (prod == 1) {
    for (int i = 0; i < sum; i++) cur_ans.push_back(1);
    if (min_ans.empty() or cur_ans.size() < min_ans.size()) {
      min_ans = cur_ans;
    }
    for (int i = 0; i < sum; i++) cur_ans.pop_back();
    return;
  }

  if (sum == 0) return;

  for (int i = 2; i <= min(sum, prod); i++) {
    if (prod % i == 0) {
      cur_ans.push_back(i);
      go(sum - i, prod / i);
      cur_ans.pop_back();
    }
  }
}

void test_case() {
  int p;
  cin >> p;

  min_ans.clear();
  cur_ans.clear();
  go(41, p);
  if (min_ans.size()) {
    cout << " " << min_ans.size();
    for (int i : min_ans) cout << " " << i;
    cout << "\n";
  }
  else cout << " -1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ":";
    test_case();
  }

  return 0;
}