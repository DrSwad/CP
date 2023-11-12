#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int computers, sockets;
  cin >> computers >> sockets;

  vector<int> computer_powers(computers);
  for (int &i : computer_powers) cin >> i;

  vector<int> socket_powers(sockets);
  for (int &i : socket_powers) cin >> i;

  vector<int> computer_order(computers);
  iota(computer_order.begin(), computer_order.end(), 0);
  sort(
    computer_order.begin(),
    computer_order.end(),
    [&](int i, int j) {
      return computer_powers[i] > computer_powers[j];
    }
  );

  vector<int> socket_order(sockets);
  iota(socket_order.begin(), socket_order.end(), 0);
  sort(
    socket_order.begin(),
    socket_order.end(),
    [&](int i, int j) {
      return socket_powers[i] > socket_powers[j];
    }
  );

  map<int, vector<int>> possible_sockets;
  for (int socket : socket_order) {
    int cur_power = socket_powers[socket];
    while (true) {
      possible_sockets[cur_power].push_back(socket);
      if (cur_power <= 1) break;
      cur_power = (cur_power + 1) / 2;
    }
  }

  vector<int> computer_with_socket(computers, -1);
  vector<int> socket_with_computer(sockets, -1);
  vector<int> socket_adapters(sockets, 0);

  int max_computers = 0, min_adapters = 0;

  for (int computer : computer_order) {
    while (!possible_sockets[computer_powers[computer]].empty()) {
      int socket = possible_sockets[computer_powers[computer]].back();
      possible_sockets[computer_powers[computer]].pop_back();

      if (socket_with_computer[socket] == -1) {
        computer_with_socket[computer] = socket;
        socket_with_computer[socket] = computer;

        while (socket_powers[socket] != computer_powers[computer]) {
          socket_adapters[socket]++;
          assert(socket_powers[socket] > 1);
          socket_powers[socket] = (socket_powers[socket] + 1) / 2;
        }

        max_computers++;
        min_adapters += socket_adapters[socket];

        break;
      }
    }
  }

  cout << max_computers << " " << min_adapters << "\n";

  for (int socket = 0; socket < sockets; socket++) {
    if (socket) cout << " ";
    cout << socket_adapters[socket];
  }
  cout << "\n";

  for (int computer = 0; computer < computers; computer++) {
    if (computer) cout << " ";
    cout << computer_with_socket[computer] + 1;
  }
  cout << "\n";

  return 0;
}