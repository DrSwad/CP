#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 100;

  vector<int> grundy(n + 1);
  grundy[0] = 0;

  for (int i = 1; i <= n; i++) {
    set<int> st;
    for (int j = 1; j <= i / 2; j++) {
      st.insert(grundy[i - j]);
    }

    int mex = 0;
    while (!st.empty() and * st.begin() == mex) {
      st.erase(st.begin());
      mex++;
    }

    grundy[i] = mex;

    if (i % 8 == 7) debug(i, grundy[i]);
  }

  return 0;
}