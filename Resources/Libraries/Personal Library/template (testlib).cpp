#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  /*
   * First command line argument
   */
  {
    int n = opt<int>(1);
  }

  /*
   * Uniformly distributed random number in the range [0, r) or [l, r]
   */
  {
    int l = opt<int>(1);
    int r = opt<int>(2);
    rnd.next(r);
    rnd.next(l, r);
  }

  /* Weighted distributed random number in the range [l, r].
   * Max/min (depending on whether w is positive/negative) over |w|+1 iterations of rnd.next(l, r).
   */
  {
    int l = opt<int>(1);
    int r = opt<int>(2);
    int w = opt<int>(3);
    rnd.wnext(l, r, w);
  }

  /*
   * Random word of (weighted) length[1, 1000]
   */
  {
    rnd.next("[a-zA-Z0-9]{1,1000}");
    int length = rnd.wnext(1, 1000, opt<int>(1));
    rnd.next("[a-zA-Z0-9]{1,%d}", length);
  }

  /*
   * Outputs random 100-digits binary string mostly containing 0's.
   * In average it contains only 10% of 1's.
   */
  {
    rnd.next("[0000000001]{100}");
  }

  /*
   * Random permutation of numbers [first, first + size)
   */
  {
    int size = opt<int>(1);
    int first = opt<int>(2);
    rnd.perm(size, first);
  }

  /*
   * Shuffle v
   */
  {
    vector<int> v = rnd.perm(10, 1);
    shuffle(v.begin(), v.end());
  }

  /*
   * Returns size unordered distinct numbers between [0, r) or [l, r]
   */
  {
    int size = opt<int>(1);
    int l = opt<int>(2);
    int r = opt<int>(3);
    rnd.distinct(size, r);
    rnd.distinct(size, l, r);
  }

  /*
   * Returns a partition of sum into size numbers each of which is at least min_part
   */
  {
    int size = opt<int>(1);
    int sum = opt<int>(2);
    int min_part = 1;
    rnd.partition(size, sum, min_part);
  }

  /*
   * Returns (weighted) random element from container
   */
  {
    set<int> st{1, 2, 5, 3};
    rnd.any(vector<int>(begin(st), end(st)));
    rnd.wany(vector<int>(begin(st), end(st)), 2);
  }

  /*
   * Print in a single line
   */
  {
    println("Hello World!!!");
  }

  return 0;
}