#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
// order_of_key(k) : number of items strictly smaller than k

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  void update(int p, T v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

const int N = 5e6 + 5;

vector<int> prime;
bool is_composite[N];
int phi[N];
int phi_chain_len[N];

void init() {
  fill(is_composite, is_composite + N, false);
  phi[1] = 1;

  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      phi[i] = i - 1;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < N; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
      else {
        phi[i * prime[j]] = phi[i] * phi[prime[j]];
      }
    }
  }

  phi_chain_len[1] = 1;
  for (int i = 2; i < N; i++) {
    phi_chain_len[i] = 1 + phi_chain_len[phi[i]];
  }
}

int n, m;
int a[N];
set<int> remaining;
ordered_set* phi_pos[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();
  
  cin >> n >> m;

  BIT<int> bit(n);

  for (int i = 1; i <= n; i++) {
    cin >> a[i];

    bit.update(i, phi_chain_len[a[i]]);

    if (a[i] > 1) remaining.insert(i);

    int val = a[i];
    while (true) {
      if (phi_pos[val] == nullptr) phi_pos[val] = new ordered_set();
      phi_pos[val]->insert(i);
      if (val == 1) break;
      val = phi[val];
    }
  }

  while (m--) {
    int t, l, r;
    cin >> t >> l >> r;

    if (t == 1) {
      auto it = remaining.lower_bound(l);
      while (it != remaining.end() and *it <= r) {
        int i = *it;

        bit.update(i, -1);
        phi_pos[a[i]]->erase(i);

        a[i] = phi[a[i]];
        if (a[i] == 1) it = remaining.erase(it);
        else it++;
      }
    }
    else {
      vector<int> vals;
      int val = a[l];
      while (true) {
        vals.push_back(val);
        if (val == 1) break;
        val = phi[val];
      }
      reverse(vals.begin(), vals.end());

      int L = 0, R = vals.size();
      while (R - L > 1) {
        int mid = (L + R) / 2;
        int val = vals[mid];
        bool okay;

        int cnt = phi_pos[val]->order_of_key(r + 1) - phi_pos[val]->order_of_key(l);
        okay = cnt == r - l + 1;

        if (okay) L = mid;
        else R = mid;
      }

      val = vals[L];
      cout << bit.range(l, r) - phi_chain_len[val] * (r - l + 1) << "\n";
    }
  }

  return 0;
}
