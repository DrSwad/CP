#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 5;

int A[N + N];
int n, k;

bool check(int x, int from = 1) {
  return 1;
}

int main() {

  cin >> n >> k;

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    A[i + n] = A[i];
    sum += A[i];
  }

  ll min_diff = LLONG_MAX, half = 0;
  int l = 0, from = -1;
  for (int i = 0; i < n; i++) {
    half += A[i];
    if (half + half >= sum) {
      if (half - (sum - half) < min_diff) {
        min_diff = half - (sum - half);
        from = i;
      }

      while (half + half >= sum) {
        half -= A[l]; l++;
      }
    }
  }

  cout << half << ' ' << from << endl;

  int lo = 1, hi = 1e9;

  // while (lo != hi) {
  //   int mid = lo + hi >> 1;
  //   if (check(mid)) lo = mid;
  //   else hi = mid - 1;
  // }

  return 0;
}