#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7 + 5;

vector<int> prime;
bool is_composite[MAXN];
int func[MAXN], cnt[MAXN];

void sieve(int n) {
  fill(is_composite, is_composite + n, false);
  func[1] = 1;

  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      func[i] = 1;
      cnt[i] = 1;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < n; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        func[i * prime[j]] = func[i] * (cnt[i] % 2 == 1 ? prime[j] : 1);
        cnt[i * prime[j]] = cnt[i] + 1;
        break;
      }
      else {
        func[i * prime[j]] = i * func[prime[j]];
        cnt[i * prime[j]] = 1;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  sieve(n + 1);

  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += func[i];
  }

  cout << ans << endl;

  return 0;
}