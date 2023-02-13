#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;
const int N = 1e4 + 4;

int n, k;
int res[N][2];

int query(string type, int i, int j) {
  assert(type == "or" or type == "and");
  cout << type << " " << i << " " << j << endl;
  int res;
  cin >> res;
  assert(res != -1);
  return res;
}

void answer(int res) {
  cout << "finish " << res << endl;
}

int main() {
  cin >> n >> k;

  for (int i = 2; i <= n; i++) {
    res[i][0] = query("or", 1, i);
    res[i][1] = query("and", 1, i);
  }

  int or23 = query("or", 2, 3);
  int and23 = query("and", 2, 3);

  int a = 0;
  for (int i = 0; i < BITS; i++) {
    if ((res[2][0] >> i & 1) == 0) continue;
    else if ((res[2][1] >> i & 1) == 1) a |= 1 << i;
    else if ((res[3][0] >> i & 1) == 0) continue;
    else if ((res[3][1] >> i & 1) == 1) a |= 1 << i;
    else if (or23 >> i & 1) continue;
    else a |= 1 << i;
  }

  vector<int> arr(n + 1, 0);
  arr[1] = a;
  for (int i = 2; i <= n; i++) {
    arr[i] |= res[i][1];
    arr[i] |= (res[i][0] ^ a);
  }

  sort(arr.begin() + 1, arr.end());
  answer(arr[k]);

  return 0;
}