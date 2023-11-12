#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<int> prime;
bool is_composite[N];
int min_prime[N];
int prime_id[N];

void sieve() {
  is_composite[1] = true;
  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      prime_id[i] = prime.size();
    }
    for (int j = 0; j < prime.size() && i * prime[j] < N; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

void init() {
  for (int i = 4; i < N; i += 2) {
    for (int p : prime) {
      if (!is_composite[i - p]) {
        min_prime[i] = p;
        break;
      }
    }
  }
}

void test_case() {
  int n;
  cin >> n;

  if (n == 2) {
    cout << "1\n2\n0\n";
  }
  else {
    int p1 = min_prime[n];
    int p2 = n - p1;

    int id1 = prime_id[p1], id2 = prime_id[p2];
    int dist = 0;
    while (id1 != id2) {
      dist++;
      if (id1 > id2) id1 >>= 1;
      else id2 >>= 1;
    }

    cout << "2\n" << p1 << " " << p2 << "\n" << dist << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();
  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}