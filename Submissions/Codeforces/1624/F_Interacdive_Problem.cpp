#include <bits/stdc++.h>
using namespace std;

int query(int c) {
  cout << "+ " << c << endl;
  int res;
  cin >> res;
  return res;
}

void answer(int ans) {
  cout << "! " << ans << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int diff = 0;
  int added = 0;
  bool is_pass_n = false;

  int prev_res = 0;
  for (int b = 9; b >= 0; b--) {
    if (1 << b >= n) continue;

    int curr_res;
    if (!is_pass_n) {
      curr_res = query(1 << b);
      added += 1 << b;
      if (curr_res == prev_res) diff |= 1 << b;
      else is_pass_n = true;
    }
    else {
      curr_res = query(n - (1 << b));
      added += n - (1 << b);
      if (curr_res == prev_res) {
        diff |= 1 << b;
        is_pass_n = false;
      }
    }

    prev_res = curr_res;
  }

  answer(n - 1 - diff + added);

  return 0;
}