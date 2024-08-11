#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;

  vector<int> v;

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int x;
      cin >> x;
      v.push_back(x);
    }
    else if (type == 2) {
      int i;
      cin >> i;
      cout << v[i - 1] << "\n";
    }
    else if (type == 3) {
      debug(v.size());
      v.pop_back();
    }
    else if (type == 4) {
      cout << v.size() << "\n";
    }
  }

  return 0;
}