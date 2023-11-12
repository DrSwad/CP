#include <bits/stdc++.h>
using namespace std;

typedef double ld;
const ld PI = acos(-1);

struct point {
  ld x, y;
  point(ld x, ld y) : x(x), y(y) {}
};

string to_string(const point &p) {
  return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

ld abs(const point &p) {
  return sqrt(p.x * p.x + p.y * p.y);
}

point operator-(const point &big, const point &small) {
  return point{big.x - small.x, big.y - small.y};
}

point operator+(const point &p1, const point &p2) {
  return point{p1.x + p2.x, p1.y + p2.y};
}

point rotate(const point &p, ld rad) {
  return point{p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad)};
}

point rotate(const point &p, const point &v) {
  ld len = abs(v);
  ld cos_v = v.x / len;
  ld sin_v = v.y / len;
  return point{p.x * cos_v - p.y * sin_v, p.x * sin_v + p.y * cos_v};
}

point cut(const point &p, ld len) {
  ld cur_len = abs(p);
  return point{p.x / cur_len * len, p.y / cur_len * len};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int n, q;
  cin >> n >> q;

  int block_size = sqrt(n);
  vector<vector<point>> blocks;
  for (int i = 1; i <= n; i++) {
    int r = i % block_size;
    if (r == 1 % block_size) blocks.push_back({point(1, 0)});
    blocks.back().push_back(r == 0 ? point(block_size + 1, 0) : point(r + 1, 0));
  }

  while (q--) {
    int type, id;
    cin >> type >> id;

    int block = (id - 1) / block_size;
    id %= block_size;
    if (id == 0) id = block_size;

    if (type == 1) {
      int len;
      cin >> len;

      point vec{blocks[block][id] - blocks[block][id - 1]};
      vec = cut(vec, len);

      for (int i = id; i <= min(block_size, (int)blocks[block].size() - 1); i++) {
        blocks[block][i] = blocks[block][i] + vec;
      }
    }
    else {
      int deg;
      cin >> deg;
      deg = 360 - deg;
      ld rad = (ld)deg / 180 * PI;

      point center = blocks[block][id - 1];
      for (int i = id; i <= min(block_size, (int)blocks[block].size() - 1); i++) {
        point diff = blocks[block][i] - center;
        diff = rotate(diff, rad);
        blocks[block][i] = diff + center;
      }
    }

    point ans = blocks.back().back();

    for (int block = (int)blocks.size() - 2; block >= 0; block--) {
      point vec{blocks[block][block_size] - blocks[block][block_size - 1]};
      ld len = abs(vec);

      ans.x += len - 1;
      ans = rotate(ans, vec);

      ans = ans + blocks[block][block_size - 1];
    }

    cout << ans.x - 1 << " " << ans.y << "\n";
  }

  return 0;
}