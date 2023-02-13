#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  map<int, int> freq;
  vector<int> arr(n);
  for (int &i : arr) {
    cin >> i;
    freq[i]++;
  }

  map<pair<int, int>, int> ranges;
  int l = -1, r = -1;
  int a = 0;
  while (true) {
    auto it = freq.lower_bound(a);
    if (it == freq.end()) {
      if (l > 0) ranges[{l, r}] = 1;
      break;
    }

    a = it->first;
    int f = it->second;

    if (f > 1) {
      freq[a + 1] += f / 2;
      f -= f / 2 * 2;
    }

    if (f == 1) {
      if (l == -1) l = a, r = a;
      else if (a != r + 1) {
        ranges[{l, r}] = 1;
        l = r = a;
      }
      else r = a;
    }

    a++;
  }

  auto insert = [&](int a) {
    vector<pair<int, int>> old_ranges;
    vector<pair<int, int>> new_ranges;

    auto it = ranges.upper_bound(make_pair(a, INF));
    if (it == ranges.begin()) {
      auto [l1, r1] = it->first;
      if (a + 1 < l1) new_ranges.push_back({a, a});
      else {
        old_ranges.push_back({l1, r1});
        new_ranges.push_back({a, r1});
      }
    }
    else {
      it--;

      auto [l1, r1] = it->first;
      if (r1 >= a) {
        old_ranges.push_back({l1, r1});
        if (l1 < a) new_ranges.push_back({l1, a - 1});
        a = r1 + 1;

        it++;
        if (it != ranges.end()) {
          auto [l2, r2] = it->first;
          if (a + 1 < l2) new_ranges.push_back({a, a});
          else {
            old_ranges.push_back({l2, r2});
            new_ranges.push_back({a, r2});
          }
        }
        else {
          new_ranges.push_back({a, a});
        }
      }
      else {
        int l = a, r = a;
        if (l == r1 + 1) {
          old_ranges.push_back({l1, r1});
          l = l1, r = a;
        }

        it++;
        if (it != ranges.end()) {
          auto [l2, r2] = it->first;
          if (r + 1 < l2) new_ranges.push_back({l, r});
          else {
            old_ranges.push_back({l2, r2});
            r = r2;
            new_ranges.push_back({l, r});
          }
        }
        else {
          new_ranges.push_back({l, r});
        }
      }
    }

    for (auto [l, r] : old_ranges) ranges.erase({l, r});
    for (auto [l, r] : new_ranges) ranges[{l, r}] = 1;
  };

  auto remove = [&](int a) {
    vector<pair<int, int>> old_ranges;
    vector<pair<int, int>> new_ranges;

    auto it = ranges.upper_bound(make_pair(a, INF));
    if (it == ranges.begin()) {
      auto [l1, r1] = it->first;
      old_ranges.push_back({l1, r1});
      new_ranges.push_back({a, l1 - 1});
      if (r1 > l1) new_ranges.push_back({l1 + 1, r1});
    }
    else {
      it--;

      auto [l1, r1] = it->first;
      if (r1 >= a) {
        old_ranges.push_back({l1, r1});
        if (l1 < a) new_ranges.push_back({l1, a - 1});
        if (r1 > a) new_ranges.push_back({a + 1, r1});
      }
      else {
        it++;
        assert(it != ranges.end());
        auto [l2, r2] = it->first;
        old_ranges.push_back({l2, r2});
        if (r2 > l2) new_ranges.push_back({l2 + 1, r2});

        if (a == r1 + 1) {
          old_ranges.push_back({l1, r1});
          new_ranges.push_back({l1, l2 - 1});
        }
        else {
          new_ranges.push_back({a, l2 - 1});
        }
      }
    }

    for (auto [l, r] : old_ranges) ranges.erase({l, r});
    for (auto [l, r] : new_ranges) ranges[{l, r}] = 1;
  };

  while (q--) {
    int i, v;
    cin >> i >> v;
    i--;

    remove(arr[i]);
    arr[i] = v;
    insert(arr[i]);

    cout << (ranges.rbegin()->first.second) << "\n";
  }

  return 0;
}