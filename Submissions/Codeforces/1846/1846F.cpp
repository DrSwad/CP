#include <bits/stdc++.h>
using namespace std;

const int A = 9;

vector<int> query(vector<int> remove, int remaining_size) {
  cout << "-";
  cout << " " << remove.size();
  for (int i : remove) cout << " " << i + 1;
  cout << endl;

  vector<int> res(remaining_size);
  for (int &i : res) cin >> i, i--;
  return res;
}

void answer(int ans) {
  cout << "! " << ans + 1 << endl;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> freq(A, 0);
  for (int i : a) freq[i]++;

  vector<int> remove;
  int queries_used = 0;

  while (true) {
    a = query(remove, n - remove.size());
    queries_used++;
    assert(queries_used <= 5);
    remove.clear();
    n = a.size();

    if (n == 1) {
      answer(0);
      return;
    }

    vector<int> nfreq(A, 0);
    for (int i : a) nfreq[i]++;

    int old = -1, cur = -1;
    for (int val = 0; val < A; val++) {
      if (nfreq[val] > freq[val]) cur = val;
      if (nfreq[val] < freq[val]) old = val;
    }
    swap(freq, nfreq);

    if (cur != -1) {
      assert(old != -1);

      if (freq[cur] == 1) {
        for (int i = 0; i < n; i++) {
          if (a[i] == cur) {
            answer(i);
            return;
          }
        }
      }

      for (int i = 0; i < n; i++) {
        if (a[i] != cur) {
          remove.push_back(i);
          freq[a[i]]--;
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}