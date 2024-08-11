#include <bits/stdc++.h>
using namespace std;

int tot_spots;
const int tot_gates = 3;
int gate_position[tot_gates];
int gate_fishermen[tot_gates];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> tot_spots;
  for (int gate = 0; gate < tot_gates; gate++) {
    cin >> gate_position[gate];
  }
  for (int gate = 0; gate < tot_gates; gate++) {
    cin >> gate_fishermen[gate];
  }

  // make sure the gate 2 is positioned at the last
  int max_index = max_element(gate_position, gate_position + tot_gates) - gate_position;
  swap(gate_position[max_index], gate_position[2]);
  swap(gate_fishermen[max_index], gate_fishermen[2]);

  // make sure the gate 0 is positioned at the first
  int min_index = min_element(gate_position, gate_position + tot_gates) - gate_position;
  swap(gate_position[min_index], gate_position[0]);
  swap(gate_fishermen[min_index], gate_fishermen[0]);

  // all the people from gate i will be placed in the spots [gate_start[i], gate_start[i] + 1, ... gate_start[i] + gate_fishermen[i] - 1]
  // in other words, all the people from gate i are placed side-by-side, starting from the spot gate_start[i]
  int gate_start[3];
  int ans = INT_MAX;

  for (gate_start[0] = 1; gate_start[0] <= tot_spots; gate_start[0]++) {
    for (gate_start[1] = gate_start[0] + gate_fishermen[0]; gate_start[1] <= tot_spots; gate_start[1]++) {
      for (gate_start[2] = gate_start[1] + gate_fishermen[1]; gate_start[2] <= tot_spots; gate_start[2]++) {
        // calculate the current answer by simply iterating over all the positions of the fishermen
        int cur_ans = 0;
        for (int gate = 0; gate < tot_gates; gate++) {
          for (int fisherman = 0; fisherman < gate_fishermen[gate]; fisherman++) {
            cur_ans += 1 + abs(gate_start[gate] + fisherman - gate_position[gate]);
          }
        }
        ans = min(ans, cur_ans);
      }
    }
  }

  cout << ans << "\n";

  return 0;
}