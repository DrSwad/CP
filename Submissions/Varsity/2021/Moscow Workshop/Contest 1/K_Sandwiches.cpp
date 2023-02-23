#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 22, Q = 3e5 + 5;
const int SZ = 2;
const int BASE[SZ] = {67, 388379}, MOD[SZ] = {1000000009, 999999937};

int n, q;
int pows[SZ][Q];
vector<int> sandwich[N];
vector<int> sandwich_hash[N];
map<vector<int>, bool> hashes;

vector<int> hash_element(int id, int eid) {
  vector<int> h(2);
  for (int it = 0; it < 2; it++) {
    h[it] = (ll)sandwich[id][eid] * pows[it][eid + 1] % MOD[it];
  }
  return h;
}

int remove(int id) {
  assert(!sandwich[id].empty());

  int sz = sandwich[id].size();
  auto h = hash_element(id, sz - 1);
  for (int it = 0; it < SZ; it++) {
    (sandwich_hash[id][it] += MOD[it] - h[it]) %= MOD[it];
  }

  int x = sandwich[id].back();
  sandwich[id].pop_back();

  return x;
}

void insert(int id, int x) {
  sandwich[id].push_back(x);
  int sz = sandwich[id].size();

  auto h = hash_element(id, sz - 1);
  for (int it = 0; it < SZ; it++) {
    (sandwich_hash[id][it] += h[it]) %= MOD[it];
  }

  hashes[sandwich_hash[id]] = true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int it = 0; it < 2; it++) {
    pows[it][0] = 1;
    for (int i = 1; i < Q; i++) {
      pows[it][i] = (ll)pows[it][i - 1] * BASE[it] % MOD[it];
    }
  }

  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    sandwich_hash[i] = vector<int>(SZ, 0);
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int id, x;
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