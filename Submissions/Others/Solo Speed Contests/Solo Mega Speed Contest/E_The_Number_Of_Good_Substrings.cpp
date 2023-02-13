#include <bits/stdc++.h>
using namespace std;

const int LOGN = 25;

void test_case() {
  string s;
  cin >> s;

  int n = s.size();
  long long ans = 0;

  for (int i = 0; i < n; i++) {
    if (s[i] != '1') continue;

    long long num = 0;
    int zeroes = 0;
    for (int j = i - 1; ~j and s[j] == '0'; j--) zeroes++;

    for (int j = i; j < n and j < i + LOGN; j++) {
      num *= 2;
      num += s[j] - '0';
      int len = j - i + 1;
      ans += len <= num and num <= len + zeroes;
    }
  }

  printf("%lld\n", ans);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}