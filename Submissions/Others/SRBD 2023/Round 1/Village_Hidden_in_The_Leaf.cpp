#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;
vector<int> prime;
bool is_composite[N];

void sieve() {
  fill(is_composite, is_composite + N, false);
  is_composite[1] = true;

  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) prime.push_back(i);
    for (int j = 0; j < prime.size() && i * prime[j] < N; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
}

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  set<int> st;
  for (int i = 0; i < n; i++) {
    if (!is_composite[a[i]]) st.insert(i);
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int i;
      cin >> i;
      i--;

      int prv, nxt;

      auto it = st.lower_bound(i);
      if (it == st.begin()) prv = -1;
      else prv = *prev(it);

      it = st.upper_bound(i);
      if (it == st.end()) nxt = n;
      else nxt = *it;

      cout << ((nxt - 1) - prv) - 1 << "\n";
    }
    else {
      int i, x;
      cin >> i >> x;
      i--;

      if (!is_composite[a[i]]) st.erase(i);
      a[i] = x;
      if (!is_composite[a[i]]) st.insert(i);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}