#include <bits/stdc++.h>
using namespace std;

const int K = 55;
const int N = 1e4 + 5;

int k;
char s[K];
int d[K];
bool is_prime[N];

void brute() {
  int min_dig = k + 1, min_val;

  for (int mask = 1; mask < 1 << k; mask++) {
    string numstr = "";
    for (int i = 0; i < k; i++) {
      if (mask >> i & 1) {
        numstr += s[i];
      }
    }

    int num = stoi(numstr, nullptr);
    if (!is_prime[num] and numstr.length() < min_dig) {
      min_dig = numstr.length();
      min_val = num;
    }
  }

  printf("%d\n%d\n", min_dig, min_val);
}

void test_case() {
  scanf("%d %s", &k, s);
  for (int i = 0; i < k; i++) d[i] = s[i] - '0';

  vector<bool> prime_digit(10, false);
  prime_digit[2] = 1;
  prime_digit[3] = 1;
  prime_digit[5] = 1;
  prime_digit[7] = 1;

  for (int i = 0; i < k; i++) {
    if (!prime_digit[d[i]]) {
      puts("1");
      printf("%d\n", d[i]);
      return;
    }
  }

  if (k <= 4) return brute();
  else {
    vector<int> freq(10, 0);
    for (int i = 0; i < k; i++) freq[d[i]]++;
    for (int i = 0; i < 10; i++) {
      if (freq[i] >= 2) {
        puts("2");
        printf("%d%d\n", i, i);
      }
    }
  }
}

int main() {
  for (int i = 2; i < N; i++) {
    is_prime[i] = true;
    for (int d = 2; d < i; d++) {
      if (i % d == 0) {
        is_prime[i] = false;
        break;
      }
    }
  }

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}