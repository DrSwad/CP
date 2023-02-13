#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

char s[N];
int t, n, z[N];

int main() {
  scanf("%s", s);
  n = strlen(s), z[0] = n;
  int L = 0, R = 0;
  for (int i = 1; i < n; ++i) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R - L] == s[R]) ++R;
      z[i] = R - L; --R;
    } else {
      int k = i - L;
      if (z[k] < R - i + 1) z[i] = z[k];
      else {
        L = i;
        while (R < n && s[R - L] == s[R]) ++R;
        z[i] = R - L; --R;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    printf("%d --> %d\n", i, z[i]);
  }
  return 0;
}

