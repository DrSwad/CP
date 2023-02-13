#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
char ans[N];
map<int, string> brute = {
  {1, "a"},
  {2, "ab"},
  {3, "abc"},
  {4, "aaba"},
  {6, "aabaaa"},
  {7, "aabaaac"},
  {10, "aaaabaaaaa"},
};

void construct(int from, int to, int used) {
  int len = to - from;

  if (brute.find(len) != brute.end()) {
    string str = brute[len];
    for (int i = from; i < to; i++) {
      ans[i] = str[i - from] + used;
    }
  }
  else {
    if (len % 3 == 0) {
      int nlen = (len - 6) / 3;
      construct(from, from + nlen, used + 2);
      ans[from + nlen] = 'a' + used;
      ans[from + nlen + 1] = 'a' + used;
      ans[from + nlen + 2] = 'b' + used;
      construct(from + nlen + 3, from + 2 * nlen + 3, used + 2);
      ans[from + 2 * nlen + 3] = 'b' + used;
      ans[from + 2 * nlen + 4] = 'b' + used;
      ans[from + 2 * nlen + 5] = 'a' + used;
      construct(from + 2 * nlen + 6, to, used + 2);
    }
    else if (len % 3 == 1) {
      int nlen = (len - 10) / 3;
      construct(from, from + nlen, used + 2);
      ans[from + nlen] = 'a' + used;
      ans[from + nlen + 1] = 'a' + used;
      ans[from + nlen + 2] = 'b' + used;
      ans[from + nlen + 3] = 'b' + used;
      ans[from + nlen + 4] = 'b' + used;
      construct(from + nlen + 5, from + 2 * nlen + 5, used + 2);
      ans[from + 2 * nlen + 5] = 'b' + used;
      ans[from + 2 * nlen + 6] = 'b' + used;
      ans[from + 2 * nlen + 7] = 'a' + used;
      ans[from + 2 * nlen + 8] = 'a' + used;
      ans[from + 2 * nlen + 9] = 'a' + used;
      construct(from + 2 * nlen + 10, to, used + 2);
    }
    else if (len % 3 == 2) {
      int nlen = (len - 2) / 3;
      construct(from, from + nlen, used + 2);
      ans[from + nlen] = 'a' + used;
      construct(from + nlen + 1, from + 2 * nlen + 1, used + 2);
      ans[from + 2 * nlen + 1] = 'b' + used;
      construct(from + 2 * nlen + 2, to, used + 2);
    }
  }
}

void test_case() {
  scanf("%d", &n);

  construct(0, n, 0);

  ans[n] = 0;
  printf("%s\n", ans);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}