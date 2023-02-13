#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 22, Q = 3e5 + 5;
const int BASE = 388379, MOD = 999999937;

int n, q;
ll pows[Q];
vector<ll> sandwich[N];
ll sandwich_hash[N];
// map<ll, bool> hashes;
set<vector<ll>> hashes;

ll remove(int id) {
  assert(!sandwich[id].empty());
  ll x = sandwich[id].back();
  int p = sandwich[id].size();
  sandwich[id].pop_back();
  (sandwich_hash[id] += MOD - x * pows[p] % MOD) %= MOD;
  return x;
}

void insert(int id, ll x) {
  sandwich[id].push_back(x);
  int p = sandwich[id].size();
  (sandwich_hash[id] += x * pows[p] % MOD) %= MOD;
  // hashes[sandwich_hash[id]] = 1;
  hashes.insert(sandwich[id]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  pows[0] = 1;
  for (int i = 1; i < Q; i++) {
    pows[i] = pows[i - 1] * BASE % MOD;
  }

  cin >> n >> q;
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int id;
      ll x;
      cin >> id >> x;
      insert(id, x);
    }
    else if (type == 2) {
      int id;
      cin >> id;
      remove(id);
    }
    else {
      int id1, id2;
      cin >> id1 >> id2;
      for (int it = 0; it < 2; it++) {
        while (sandwich[id1].size() > sandwich[id2].size() + 1) {
          insert(id2, remove(id1));
        }
        swap(id1, id2);
      }
    }
  }

  cout << hashes.size() << "\n";

  return 0;
}