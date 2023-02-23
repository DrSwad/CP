#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int get(char s[], int n) {
  vector<int> segs{1};
  for (int i = 1; i < n; i++) {
    if (s[i] == s[i - 1]) segs.back()++;
    else segs.push_back(1);
  }
  if (segs.size() > 1 and s[n - 1] == s[0]) {
    segs[0] += segs.back();
    segs.pop_back();
  }
  return *max_element(segs.begin(), segs.end());
}

int main() {
  int t;
  scanf("%d", &t);

  char s[N];
  for (int cs = 1; cs <= t; cs++) {
    scanf("%s", s);
    int n = strlen(s);

    int ans = n;
    for (int i = 0; i < n; i++) {
      char c = s[i];
      if (s[i] == 'R') s[i] = 'A';
      else s[i] = 'R';
      ans = min(ans, get(s, n));
      s[i] = c;
    }
    printf("Case %d: %d\n", cs, ans);
  }

  return 0;
}