#include <bits/stdc++.h>
using namespace std;

#define FRONT 0
#define RIGHT 1
#define BACK 2
#define LEFT 3
#define TOP 4
#define BOTTOM 5

// coloring order: {front, right, back, left, top, bottom}
set<string> found_cubes;

string rotate_right(string colors) {
  string new_colors = colors;
  for (int i = 0; i < 4; i++) {
    new_colors[i] = colors[(i - 1 + 4) % 4];
  }
  return new_colors;
}

string rotate_up(string colors) {
  string new_colors = colors;
  // new_colors = {old_bottom, old_right, old_top, old_left, old_front, old_back}
  new_colors[FRONT] = colors[BOTTOM];
  new_colors[BACK] = colors[TOP];
  new_colors[TOP] = colors[FRONT];
  new_colors[BOTTOM] = colors[BACK];
  return new_colors;
}

bool find_sideways(string cube) {
  for (int i = 0; i < 4; i++) {
    if (found_cubes.find(cube) != found_cubes.end()) return true;
    cube = rotate_right(cube);
  }
  return false;
}

bool find_identical_cubes(string cube) {
  for (int i = 0; i < 4; i++) {
    if (find_sideways(cube)) return true;
    cube = rotate_up(cube);
  }

  cube = rotate_right(cube);
  cube = rotate_up(cube);
  if (find_sideways(cube)) return true;

  cube = rotate_up(cube);
  cube = rotate_up(cube);
  if (find_sideways(cube)) return true;

  return false;
}

void test_case() {
  found_cubes.clear();

  vector<int> freq(6, 0);
  vector<char> char_ids{'R', 'G', 'B', 'Y', 'W', 'O'};

  char c;
  for (int i = 0; i < 6; i++) {
    cin >> c;
    int id = find(char_ids.begin(), char_ids.end(), c) - char_ids.begin();
    assert(0 <= id and id < 6);
    freq[id]++;
  }

  string s;
  function<void(int)> go =
    [&](int at) {
      if (at == 6) {
        if (!find_identical_cubes(s)) {
          found_cubes.insert(s);
        }
        return;
      }

      for (int i = 0; i < 6; i++) {
        if (freq[i] > 0) {
          s += char_ids[i];
          freq[i]--;
          go(at + 1);
          s.pop_back();
          freq[i]++;
        }
      }
    };

  go(0);

  cout << found_cubes.size() << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}