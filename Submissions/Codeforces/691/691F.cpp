#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
const int A = 3e6;

int n;
int freq[A + 1];
long long suffix_sum[A + 1];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    freq[a]++;
  }

  for (int i = 1; i <= A; i++) {
    int rem = n;
    for (int j = i, q = 1; j <= A; j += i, q++) {
      suffix_sum[j] += 1ll * freq[i] * (q == i ? freq[i] - 1 : freq[q]);
      rem -= freq[q];
    }
    if (1ll * i * i > A) rem--;
    suffix_sum[A] += 1ll * freq[i] * rem;
  }

  for (int i = A - 1; i >= 1; i--) {
    suffix_sum[i] += suffix_sum[i + 1];
  }

  int q;
  cin >> q;

  while (q--) {
    int p;
    cin >> p;

    cout << suffix_sum[p] << "\n";
  }

  return 0;
}