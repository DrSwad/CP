#include <bits/stdc++.h>
using namespace std;

int main() {
  int a = 0;
  for (int i = 0; i <= 5e7; i++) {
    a += i * i;
  }
  cout << a << endl;

  return 0;
}