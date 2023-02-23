#include <bits/stdc++.h>
using namespace std;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch())
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

int query(vector<int> &v) {
  cout << "? " << v.size();
  for (int i : v) cout << " " << i;
  cout << endl;

  int res;
  cin >> res;
  return res;
}

void answer(bool ans) {
  cout << "! " << (ans ? "YES" : "NO") << endl;
}

void test_case() {
  int n;
  cin >> n;

  int total;
  vector<int> v(n);
  iota(v.begin(), v.end(), 1);
  total = query(v);

  bool possible = true;

  for (int i = 1; i <= 29; i++) {
    shuffle(v.begin(), v.end(), rng);
    int szA = uniform_int_distribution<int>(1, n - 1)(rng);

    vector<int> A = vector<int>(v.begin(), v.begin() + szA);
    vector<int> B = vector<int>(v.begin() + szA, v.begin() + n);

    int resA = query(A);
    int resB = query(B);

    if ((resA + resB) % 2 != total % 2) {
      possible = false;
      break;
    }
  }

  answer(possible);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}