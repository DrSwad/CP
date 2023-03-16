#include <bits/stdc++.h>
using namespace std;

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  int n;
  cin >> n;

  vector<pair<int, string>> v;
  for (int i = 0; i < n; i++) {
    string name;
    int penalty;
    cin >> name >> penalty;
    v.emplace_back(penalty, name);
  }

  sort(v.begin(), v.end());

  printf("Selise Coding Challenge 2023 Winners\n");
  printf("Winner: %s => %d\n", v[0].second.c_str(), v[0].first);
  printf("1st Runner Up: %s => %d\n", v[1].second.c_str(), v[1].first);
  printf("2nd Runner Up: %s => %d\n", v[2].second.c_str(), v[2].first);

  return 0;
}
