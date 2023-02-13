#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int M = N * N * N * N;

bool is_prime[M];

void init() {
  fill(is_prime + 1, is_prime + M, true);
  for (int i = 2; i < M; i++) {
    if (is_prime[i]) {
      for (int j = 2 * i; j < M; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

int n, b;

void print(vector<int> nums) {
  vector<vector<int>> mat(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = i, k = 0; k < n; k++, j = (j + 1) % n) {
      mat[i][k] = nums[j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) cout << " ";
      cout << mat[i][j];
    }
    cout << "\n";
  }

  exit(EXIT_SUCCESS);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, b;
  cin >> n >> b;

  if (b < n * n) cout << "impossible\n";
  else {
    uniform_int_distribution<int> uid(1, b);
    auto gen = bind(uid, rng);

    vector<int> nums(b);
    iota(nums.begin(), nums.end(), 1);

    for (int i = 1; i <= 100; i++) {
      shuffle(nums.begin(), nums.end(), rng);
      if (is_prime[accumulate(nums.begin(), nums.end() + n, 0)]) {
        print(vector<int>(nums.begin(), nums.begin() + n));
      }
    }

    cout << "impossible\n";
  }

  return 0;
}