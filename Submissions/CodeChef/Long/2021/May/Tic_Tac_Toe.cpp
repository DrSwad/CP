#include <bits/stdc++.h>
using namespace std;

char a[3][3];

bool checkRowsForWinner(char winner) {
  for (int row = 0; row < 3; row++) {
    map<char, int> cnt;
    for (int col = 0; col < 3; col++) {
      cnt[a[row][col]]++;
    }
    if (cnt[winner] == 3) return true;
  }
  return false;
}

bool checkColumnsForWinner(char winner) {
  for (int col = 0; col < 3; col++) {
    map<char, int> cnt;
    for (int row = 0; row < 3; row++) {
      cnt[a[row][col]]++;
    }
    if (cnt[winner] == 3) return true;
  }
  return false;
}

bool checkDiagonalsForWinner(char winner) {
  map<char, int> cnt;
  for (int row = 0; row < 3; row++) {
    cnt[a[row][row]]++;
  }
  if (cnt[winner] == 3) return true;

  cnt.clear();
  for (int row = 0; row < 3; row++) {
    cnt[a[row][2 - row]]++;
  }
  if (cnt[winner] == 3) return true;

  return false;
}

bool hasWon(char winner) {
  return checkRowsForWinner(winner) or checkColumnsForWinner(winner) or checkDiagonalsForWinner(winner);
}

bool hasDrawn() {
  if (hasWon('X') or hasWon('O')) return false;
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (a[row][col] == '_') return false;
    }
  }
  return true;
}

bool hasNotEnded() {
  return !hasWon('X') and !hasWon('O') and !hasDrawn();
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int cntX = 0, cntO = 0;

    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        scanf(" %c", &a[row][col]);
        cntX += a[row][col] == 'X';
        cntO += a[row][col] == 'O';
      }
    }

    if (cntX<cntO or cntX> cntO + 1) puts("3");
    else if (hasNotEnded()) puts("2");
    else if (hasDrawn()) puts("1");
    else if (hasWon('X') and hasWon('O')) puts("3");
    else {
      char winner = cntX > cntO ? 'X' : 'O';
      if (!hasWon(winner)) puts("3");
      else {
        int ans = 3;
        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 3; col++) {
            if (a[row][col] == winner) {
              a[row][col] = '_';
              if (hasNotEnded()) ans = 1;
              a[row][col] = winner;
            }
          }
        }
        printf("%d\n", ans);
      }
    }
  }

  return 0;
}