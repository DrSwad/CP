#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int D = 40;

string sum;
int freq[D];
int n;

void reset() {
  memset(freq, 0, sizeof freq);
}

void test_case() {
  cin >> sum >> n;
  while (sum.length() < D) sum = "0" + sum;

  for (int i = 0; i < D; i++) {
    freq[i] = sum[i] - '0';
  }

  while (accumulate(freq, freq + D, 0) < n) {
    for (int i = D - 2; i >= 0; i--) {
      if (freq[i]) {
        freq[i]--;
        freq[i + 1] += 10;
        break;
      }
    }
  }

  vector<string> s(n, string(D, '0'));

  int needs = 0;
  for (int i = 0; i < D; i++) {
    while (freq[i] and needs < n) {
      s[needs++][i] = '1';
      freq[i]--;
    }

    for (int j = 0; j < n and freq[i]; j++) {
      int take = min(freq[i], '9' - s[j][i]);
      s[j][i] += take;
      freq[i] -= take;
    }
  }

  for (int i = 0; i < n; i++) {
    bool flag = false;
    for (int j = 0; j < D; j++) {
      if (flag or s[i][j] != '0') {
        flag = true;
        printf("%c", s[i][j]);
      }
    }
    assert(flag);
    if (i < n - 1) printf(" ");
  }
  puts("");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}