#include <bits/stdc++.h>
using namespace std;

const int A = 1e7 + 5;

vector<int> prime;
bool is_composite[A];
int smallest_prime_fact[A];
vector<int> prime_facts[A];

void sieve() {
  fill(is_composite, is_composite + A, false);

  for (int i = 2; i < A; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      smallest_prime_fact[i] = i;
      prime_facts[i].push_back(i);
    }
    for (int j = 0; j < prime.size() && i * prime[j] < A; j++) {
      int v = i * prime[j];
      is_composite[v] = true;
      smallest_prime_fact[v] = min(prime[j], smallest_prime_fact[i]);
      prime_facts[v] = prime_facts[i];
      if (i % prime[j] == 0) break;
      else prime_facts[v].push_back(prime[j]);
    }
  }
}

bool solve(vector<int> a, vector<int> b) {
  map<int, int> p_vis;
  for (int i : a) {
    for (int p : prime_facts[i]) {
      p_vis[p] = true;
    }
  }

  for (int i : b) {
    for (int p : prime_facts[i]) {
      if (p_vis.find(p) == p_vis.end()) {
        return false;
      }
    }
  }

  return true;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int ga = a[0], gb = b[0];
  for (int i = 1; i < n; i++) {
    ga = __gcd(ga, a[i]);
    gb = __gcd(gb, b[i]);
  }

  bool ans_1 = solve(a, b);
  bool ans_2 = solve({ga}, {gb});
  for (int i = 0; i < n; i++) {
    ans_2 = ans_2 and a[i] / ga == b[i] / gb;
  }

  cout << " " << (ans_1 ? "Yes" : "No");
  cout << " " << (ans_2 ? "Yes" : "No");
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ":";
    test_case();
  }

  return 0;
}