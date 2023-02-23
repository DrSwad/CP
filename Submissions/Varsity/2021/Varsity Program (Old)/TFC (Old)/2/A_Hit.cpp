#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cerr << fixed << setprecision(2);

  int width, height, distance;
  cin >> width >> height >> distance;

  int vx, vy, vz;
  cin >> vx >> vy >> vz;
  vy = -vy;

  double pos_x = width / 2.0, pos_y = -distance, pos_z = 0;

  const double eps = 1e-6;
  const int INF = 1e9;
  while (fabs(pos_y) > eps) {
    double tx, ty, tz;

    if (vx != 0) tx = (double)(vx > 0 ? width - pos_x : pos_x - 0) / abs(vx);
    else tx = INF;

    ty = (double)(0 - pos_y) / vy;

    if (vz != 0) tz = (double)(vz > 0 ? height - pos_z : pos_z - 0) / abs(vz);
    else tz = INF;

    double tm = min(tx, min(ty, tz));

    pos_x += vx * tm;
    pos_y += vy * tm;
    pos_z += vz * tm;

    if (fabs(tm - tx) <= eps) vx = -vx;
    if (fabs(tm - ty) <= eps) vy = -vy;
    if (fabs(tm - tz) <= eps) vz = -vz;
  }

  cout << fixed << setprecision(15) << pos_x << " " << pos_z << "\n";

  return 0;
}