#include <bits/stdc++.h>
using namespace std;

vector<int> tasks;
vector<int> workers;
int pills;
int strength;

bool check(int take) {
  if (take == 0) return true;
  int nt = tasks.size(), nw = workers.size();
  int pills_remaining = pills;

  multiset<int> st(tasks.begin(), tasks.begin() + take);
  multiset<int> sw(workers.end() - take, workers.end());

  while (take) {
    if (*st.begin() > *sw.begin()) {
      if (!pills_remaining) return false;
      pills_remaining--;
      sw.insert(*sw.begin() + strength);
      sw.erase(*workers.begin());
    }
    if (*st.begin() > *sw.begin()) return false;
    st.erase(*st.begin());
    sw.erase(*sw.begin());
  }

  return true;
}

int test_case() {
  tasks = {5, 9, 8, 5, 9}, workers = {1, 6, 4, 2, 6}, pills = 1, strength = 5;

  int nt = tasks.size(), nw = workers.size();
  sort(tasks.begin(), tasks.end());
  sort(workers.begin(), workers.end());
  debug(tasks);
  debug(workers);

  int L = 0, R = min(nt, nw);
  while (L != R) {
    int m = (L + R + 1) / 2;
    if (check(m)) L = m;
    else R = m - 1;
  }

  return L;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    cout << test_case() << "\n";
  }

  return 0;
}