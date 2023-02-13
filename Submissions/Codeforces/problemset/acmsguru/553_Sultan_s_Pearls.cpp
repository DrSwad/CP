#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;

int n, m, k;
int w[N], c[N];
int pref_w[N], pref_c[N];
int ans_sum, ans_head, ans_tail;

void take_from_tail(int tail) {
  int min_need_head = 0, max_need_head = n - tail - m;
  while (min_need_head != max_need_head) {
    int need_head = (min_need_head + max_need_head) / 2;
    int head = n - tail - m;
    if ((pref_w[head] - pref_w[head - need_head]) * k >= pref_w[head + m] - pref_w[head]) max_need_head = need_head;
    else min_need_head = need_head + 1;
  }

  int need_head = min_need_head;
  int head = n - tail - m - need_head;
  int curr_sum = pref_c[head] + (pref_c[n] - pref_c[n - tail]);
  if (curr_sum >= ans_sum) {
    ans_sum = curr_sum;
    ans_head = head;
    ans_tail = tail;
  }
}

int main() {
  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) {
    cin >> w[i] >> c[i];
  }

  pref_w[0] = pref_c[0] = 0;
  for (int i = 1; i <= n; i++) {
    pref_w[i] = pref_w[i - 1] + w[i];
    pref_c[i] = pref_c[i - 1] + c[i];
  }

  for (int tail = 0; tail <= n; tail++) {
    int head = n - tail - m;
    if (head < 0) break;
    if (pref_w[head] * k < pref_w[head + m] - pref_w[head]) break;
    take_from_tail(tail);
  }

  if (ans_sum == 0) cout << "0 0\n";
  else {
    cout << ans_head + ans_tail << " " << ans_sum << "\n";
    for (int i = 0; i < ans_tail; i++) cout << 'H';
    for (int i = 0; i < ans_head; i++) cout << 'T';
    cout << "\n";
  }

  return 0;
}