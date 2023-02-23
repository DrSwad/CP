#include <bits/stdc++.h>
using namespace std;

vector<bool> states;

pair<int, int> getIntersectionID(int id1, int id2) {
  if (id1 > id2) swap(id1, id2);
  assert(id1 != id2);

  int i1, i2;
  if (id1 == 0 and id2 == 1) i1 = 0, i2 = 3;
  else if (id1 == 0 and id2 == 2) i1 = 1, i2 = 4;
  else if (id1 == 1 and id2 == 2) i1 = 2, i2 = 5;
  else assert(69 == 420);

  return {i1, i2};
}

bool doesIntersect(int id1, int id2) {
  auto [i1, i2] = getIntersectionID(id1, id2);
  return states[i1] != states[i2];
}

bool isInOrder(int id1, int id2) {
  assert(!doesIntersect(id1, id2));
  auto [i1, i2] = getIntersectionID(id1, id2);
  if (id1 < id2) return states[i1] and states[i2];
  else return !states[i1] and !states[i2];
}

int main() {
  for (int i = 0; i < 6; i++) {
    string s;
    cin >> s;
    states.push_back(s == string("true"));
  }

  int ans = 4;
  ans += !doesIntersect(0, 1);
  ans += !doesIntersect(0, 2);
  ans += !doesIntersect(1, 2);
  if (ans == 7) {
    int id1 = 0, id2 = 1;
    if (!isInOrder(id1, id2)) swap(id1, id2);
    int id3 = 2;
    if (isInOrder(id3, id1) and isInOrder(id3, id2)) ans++;
    else if (isInOrder(id1, id3) and isInOrder(id2, id3)) ans++;
    else if (isInOrder(id1, id3) and isInOrder(id3, id2)) ans++;
  }

  cout << ans << endl;

  return 0;
}