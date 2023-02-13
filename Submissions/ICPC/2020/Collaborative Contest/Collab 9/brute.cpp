#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

int n, k;
int div_count[N];
int par[N];

void sieve() {
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j += i) {
      div_count[j]++;
    }
  }
}

ll go(int from) {
  ll sum = 0;
  for (int i = 0, at = from; i < k; i++, at = par[at]) {
    if (at == -1) return -1;
    sum += at;
  }
  return sum;
}

int main() {
  scanf("%d %d", &n, &k);
  if (k > n) {
    puts("-1");
    return 0;
  }

  sieve();

  par[0] = -1;
  for (int i = 1; i < n; i++) {
    par[i] = (i + div_count[i]) % n;
  }

  ll ans = -1;
  int ans_from;
  for (int i = 0; i < n; i++) {
    ll curr = go(i);
    if (~curr and (ans == -1 or curr < ans)) {
      ans = curr;
      ans_from = i;
    }
  }

  for (int i = 0, at = ans_from; i < k; i++, at = par[at]) {
    if (i) printf(" ");
    printf("%d", at);
  }
  puts("");

  return 0;
}