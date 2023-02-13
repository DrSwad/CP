#include <bits/stdc++.h>
using namespace std;

const int B = 5;
const int C = 26;

vector<int> query(int mask) {
  string s;
  for (int c = 0; c < C; c++) {
    if ((c & mask) == mask) {
      s += 'a' + c;
    }
  }
  cout << "? " << s << endl;

  int sz;
  cin >> sz;
  vector<int> res(sz);
  for (int &i : res) cin >> i, i--;

  return res;
}

void answer(string ans) {
  cout << "! " << ans << endl;
  exit(EXIT_SUCCESS);
}

int main() {
  vector<vector<int>> sets(2 * B);

  int n = query(0).size();

  for (int b = 0; b < B; b++) {
    sets[b << 1] = query(1 << b);
    vector<bool> vis(n, false);
    for (int i : sets[b << 1]) vis[i] = true;
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        sets[b << 1 | 1].push_back(i);
      }
    }
  }

  string ans(n, '0');

  for (int c = 0; c < 26; c++) {
    vector<int> freq(n, 0);
    for (int b = 0; b < B; b++) {
      int id = (b << 1) + ((c >> b & 1) == 0);
      for (int i : sets[id]) freq[i]++;
    }

    for (int i = 0; i < n; i++) {
      if (freq[i] == B) {
        ans[i] = 'a' + c;
      }
    }
  }

  answer(ans);

  return 0;
}