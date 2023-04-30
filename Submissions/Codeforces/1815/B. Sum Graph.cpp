#include <bits/stdc++.h>
using namespace std;

int n;

void query1(int x) {
  assert(2 <= x and x <= 2 * n);
  cout << "+ " << x << endl;
  int res;
  cin >> res;
  assert(res == 1);
}

int query2(int i, int j) {
  assert(1 <= i and i <= n);
  assert(1 <= j and j <= n);
  cout << "? " << i << " " << j << endl;
  int r;
  cin >> r;
  return r;
}

void answer(const vector<int> &p1, const vector<int> &p2) {
  cout << "!";
  for (int i = 1; i <= n; i++) cout << " " << p1[i];
  for (int i = 1; i <= n; i++) cout << " " << p2[i];
  cout << endl;
  int res;
  cin >> res;
  assert(res == 1);
}

vector<int> get_perm(int p_1, const vector<int> &dist, const vector<int> &bamboo) {
  assert(p_1 == bamboo[1] or p_1 == bamboo[n]);
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++) {
    int index = p_1 == bamboo[1] ? 1 + dist[i] : n - dist[i];
    p[i] = bamboo[index];
  }
  return p;
}

void test_case() {
  cin >> n;

  query1(1 + n);
  query1(2 + n);

  vector<int> bamboo;
  bamboo.push_back(-1);
  for (int i = 1; i <= (n + 1) / 2; i++) {
    bamboo.push_back(i);
    int j = n + 1 - i;
    if (j != i) bamboo.push_back(j);
  }

  int max_dist = -1, max_dist_with = -1;
  for (int i = 2; i <= n; i++) {
    int dist = query2(1, i);
    if (dist > max_dist) {
      max_dist = dist;
      max_dist_with = i;
    }
  }

  int fix = max_dist_with;

  vector<int> dist(n + 1);
  dist[fix] = 0;
  for (int i = 1; i <= n; i++) {
    if (i == fix) continue;
    dist[i] = query2(fix, i);
    assert(dist[i] != -1);
    assert(0 <= dist[i] and dist[i] <= n - 1);
  }

  for (int d = 0; d < n; d++) {
    assert(find(dist.begin(), dist.end(), d) != dist.end());
  }

  vector<int> p1 = get_perm(bamboo[1], dist, bamboo);
  vector<int> p2 = get_perm(bamboo[n], dist, bamboo);
  answer(p1, p2);
}

int main() {
  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
