#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  priority_queue<int> pq;
  long long sum = 0;

  while (n--) {
    int a;
    cin >> a;
    pq.push(-a);
    sum += a;
  }

  while (m--) {
    int b;
    cin >> b;

    sum -= -pq.top();
    pq.pop();
    sum += b;
    pq.push(-b);
  }

  cout << sum << "\n";
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