#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> names{"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue"};
  map<string, int> name_id;
  for (int i = 0; i < names.size(); i++) {
    name_id[names[i]] = i;
  }

  char name1[20], name2[20];
  scanf("%s must be milked beside %s", name1, name2);
  string str1(name1), str2(name2);
  int id1 = name_id[str1], id2 = name_id[str2];
  cout << id1 << " " << id2 << endl;

  return 0;
}