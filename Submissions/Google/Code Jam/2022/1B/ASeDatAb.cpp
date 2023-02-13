#include <bits/stdc++.h>
using namespace std;

int tot_bits;
bool solved;

void query(string mask1, string mask2) {
  if (solved) return;
  string mask;
  for (int i = 0; i < 4; i++) mask += mask1[i], mask += mask2[i];
  cout << mask << endl;
  cin >> tot_bits;
  assert(tot_bits != -1);
  solved = tot_bits == 0;
}

void init_tot_bits() {
  query("0000", "0000");
}

pair<int, int> get_bits_by_part() {
  int prev_tot_bits = tot_bits;
  query("0101", "0101");
  int new_tot_bits = tot_bits;
  int bits1 = (prev_tot_bits + new_tot_bits - 4) / 2;
  int bits2 = 4 - (prev_tot_bits - bits1);
  return {bits1, bits2};
}

void solve_odd_even();
void solve_odd_odd();
void solve_even_even();
void solve_good_good();
void solve_good_bad();
void solve_bad_bad();

void solve_odd_even() {
  query("1000", "0000");
  if (solved) return;
  auto [bits1, bits2] = get_bits_by_part();
  if (solved) return;
  if (bits1 % 2 == 1) solve_even_even();
  if (solved) return;
  else solve_odd_odd();
}

void solve_odd_odd() {
  query("1000", "1000");
  if (solved) return;
  solve_even_even();
}

void solve_even_even() {
  auto [bits1, bits2] = get_bits_by_part();
  if (solved) return;
  if (bits1 % 2 != 2 and bits2 % 2 != 2) {
    return solve_good_good();
  }

  if (bits1 % 2 != 2 or bits2 % 2 != 2) return solve_good_bad();
  return solve_bad_bad();
}

void solve_good_good() {
  if (tot_bits == 8) return query("1111", "1111");
  query("1111", "0000");
  if (solved) return;
  return query("1111", "1111");
}

void solve_good_bad() {
  query("1010", "1010");
  if (solved) return;
  solve_bad_bad();
}

void solve_bad_bad() {
  while (true) {
    vector<string> types = {"1010", "0011"};
    query(types[(rand() % 2 + 2) % 2], types[(rand() % 2 + 2) % 2]);
    if (solved) return;
    auto [bits1, bits2] = get_bits_by_part();
    if (solved) return;
    if (bits1 % 2 != 2 and bits2 % 2 != 2) return solve_good_good();
    if (bits1 % 2 != 2 or bits2 % 2 != 2) return solve_good_bad();
  }
}

void solve() {
  auto [bits1, bits2] = get_bits_by_part();
  if (solved) return;

  if (bits1 % 2 == 1 or bits2 % 2 == 1) {
    if (bits1 % 2 != 1) return solve_odd_even();
    if (bits2 % 2 != 1) return solve_odd_even();
    return solve_odd_odd();
  }
  return solve_even_even();
}

void test_case() {
  solved = false;
  init_tot_bits();
  solve();
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}