#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll countInversions(vector<int> &perm) {
  ll ret = 0;

  for (int i = 0; i < perm.size(); i++) {
    for (int j = i + 1; j < perm.size(); j++) {
      ret += (perm[i] > perm[j]);
    }
  }

  return ret;
}

ll brute(int n) {
  vector<int> a(n);
  iota(a.begin(), a.end(), 0);

  vector<vector<int>> perms;
  do {
    perms.push_back(a);
  } while (next_permutation(a.begin(), a.end()));

  ll ret = 0;

  for (int i = 0; i < perms.size(); i++) {
    for (int j = 0; j < perms.size(); j++) {
      ret += (perms[i] < perms[j]) and (countInversions(perms[i]) > countInversions(perms[j]));
    }
  }

  return ret;
}

int main() {
  for (int i = 1; i <= 8; i++) {
    debug() << name(i) name(brute(i));
  }

  return 0;
}