#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 16;
int n, k;
vector<int> with;

void brute(int at) {
  if (at == n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      sum += i & with[i];
    }
    sum /= 2;
    debug(sum, with);
    return;
  }

  if (with[at] != -1) brute(at + 1);
  else {
    for (int i = 0; i < n; i++) {
      if (i != at and with[i] < 0) {
        with[i] = at;
        with[at] = i;
        brute(at + 1);
        with[i] = -1;
        with[at] = -1;
      }
    }
  }
}

void test_case() {
  cin >> n >> k;

  with.resize(n, -1);
  brute(0);
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