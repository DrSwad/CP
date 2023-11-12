#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> big_pos;
  for (int i = 0; i < n; i++) {
    if (a[i] > 1) {
      big_pos.push_back(i);
    }
  }

  if (big_pos.empty()) {
    cout << "1 1\n";
    return;
  }
  else if (big_pos.size() == 1) {
    cout << big_pos[0] + 1 << " " << big_pos[0] + 1 << "\n";
    return;
  }

  ll sum = 0;
  for (int i : a) sum += i;

  ll prod_limit = sum + 5 * n;
  ll prod = 1;
  bool okay = true;

  for (int i = 0; i < n; i++) {
    if (prod_limit / a[i] < prod) {
      okay = false;
      break;
    }
    prod *= a[i];
  }

  if (!okay) {
    cout << big_pos[0] + 1 << " " << big_pos.back() + 1 << "\n";
    return;
  }

  vector<ll> prefix_sum(n + 1), prefix_prod(n + 1);
  prefix_sum[0] = 0;
  prefix_prod[0] = 1;
  for (int i = 0; i < n; i++) {
    prefix_sum[i + 1] = prefix_sum[i] + a[i];
    prefix_prod[i + 1] = prefix_prod[i] * a[i];
  }

  ll max_sum = 0;
  int l, r;

  for (int i = 0; i < big_pos.size(); i++) {
    for (int j = i; j < big_pos.size(); j++) {
      int pos_i = big_pos[i];
      int pos_j = big_pos[j];
      ll cur_sum = (prefix_sum[n] - (prefix_sum[pos_j + 1] - prefix_sum[pos_i])) +
                   (prefix_prod[pos_j + 1] / prefix_prod[pos_i]);
      if (cur_sum > max_sum) {
        max_sum = cur_sum;
        l = pos_i + 1;
        r = pos_j + 1;
      }
    }
  }

  cout << l << " " << r << "\n";
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