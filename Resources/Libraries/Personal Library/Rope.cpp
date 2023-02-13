/*
 * Problem: Given an array of length n, you will be given q queries
            Each query will contain two indexes L and R (L >= R)
            You have to move the segment [L, R] to the beginning of the array
            All the indices are zero based
 */

#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

rope<int> R; // use as usual STL container

int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    R.push_back(a);
  }

  int l, r;
  for (int i = 0; i < q; ++i) {
    cin >> l >> r;
    rope<int> cur = R.substr(l, r - l + 1);
    R.erase(l, r - l + 1);
    R.insert(0, cur);
  }
  for (auto it = R.mutable_begin(); it != R.mutable_end(); ++it) cout << *it << " ";
  cout << "\n";
  return 0;
}

/*
 * For character ropes, we can use "crope" instead of "rope<char>".
 * crope r = "abcdef";

 * Initialization: rope<int> R(n, 0);

 * R.push_back(x) inserts element x at the end of rope R.
   Time Complexity: O(log N).

 * R.pop_back() deletes the last element from the rope R.
   Time Complexity: O(log N).

 * R.insert(pos, nr) inserts rope nr into R at position pos (the first element of nr will be in position pos).
   Time Complexity: For Best Case: O(log N) and For Worst Case: O(N).

 * R.erase(pos, cnt) deletes segment [pos, pos + cnt) from R.
   Time Complexity: O(log N).

 * R.substr(pos, cnt) = segment[pos, pos + cnt).
   Time Complexity: O(log N).

 * R.replace(pos, cnt, nr) replaces the segment [pos, pos + cnt) with the rope nr.
   Time Complexity: O(log N).

 * R1 + R2: concatenate two ropes using the ‘+’ symbol.
   Time Complexity: O(1).

 * R.size(): Returns the length of the rope R.
 * R.mutable_begin(): Returns an iterator pointing to the beginning of the rope R.
 * R.mutable_end(): Returns an iterator pointing to the end of the rope R.
 * R.mutable_reference_at(pos): Mutable reference pointing at pos
 */
