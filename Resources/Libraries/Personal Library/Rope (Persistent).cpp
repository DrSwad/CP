// Persistent Rope
//
// Description:
//   Rope is a binary tree data structure to maintains a sequence.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <map>
#include <cmath>
#include <cstring>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define x first
#define y second

struct rope {
  struct node {
    char v;
    node *l, *r;
    int s;
    node(char v, node *l, node *r) : v(v), l(l), r(r) {
      s = 1 + (l ? l->s : 0) + (r ? r->s : 0);
    }
  } *root;
  node* join(node *a, node *b) {
    auto R = [](int a, int b) { return rand() % (a + b) < a; };
    if (!a || !b) return a ? a : b;
    if (R(a->s, b->s)) return new node(a->v, a->l, join(a->r, b));
    else return new node(b->v, join(a, b->l), b->r);
  }
  pair<node*, node*> split(node *a, int s) {
    if (!a || s <= 0) return {0, a};
    if (a->s <= s) return {a, 0};
    if (a->l && s <= a->l->s) {
      auto p = split(a->l, s);
      return {p.x, new node(a->v, p.y, a->r)};
    } else {
      auto p = split(a->r, s - (a->l ? a->l->s : 0) - 1);
      return {new node(a->v, a->l, p.x), p.y};
    }
  }
  pair<node*, node*> cut(node *a, int l, int r) { // (sub, rest)
    if (l >= r) return {0, a};
    auto p = split(a, l), q = split(p.y, r - l);
    return {q.x, join(p.x, q.y)};
  }
  rope(const char s[]) {
    function<node*(int, int)> build = [&](int l, int r) {
      if (l >= r) return (node*)0;
      int m = (l + r) / 2;
      return new node(s[m], build(l, m), build(m + 1, r));
    };
    root = build(0, strlen(s));
  }
  rope(rope::node *r) : root(r) { }
  int size() const { return root ? root->s : 0; }
  rope insert(int k, const char s[]) {
    auto p = split(root, k);
    return {join(p.x, join(rope(s).root, p.y))};
  }
  rope substr(int l, int r) { return {cut(root, l, r).x}; }
  rope erase(int l, int r) { return {cut(root, l, r).y}; }
  char at(int k) const {
    function<char(node*)> rec = [&](node *a) {
      int s = a->l ? a->l->s : 0;
      if (k == s) return a->v;
      if (k < s) return rec(a->l);
      k -= s + 1; return rec(a->r);
    };
    return rec(root);
  }
  string str() const {
    stringstream ss;
    function<void(node*)> rec = [&](node *a) {
      if (!a) return;
      rec(a->l); ss << a->v; rec(a->r);
    }; rec(root);
    return ss.str();
  }
};

int main() {
  rope a("abcde"), b("ABCDE");
  for (int i = 0; i < 5; ++i) {
    cout << a.at(i) << " ";
  }
}
