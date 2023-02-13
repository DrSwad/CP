#include <bits/stdc++.h>
using namespace std;

string s[2];
vector<string> lists[2];
vector<pair<int, int>> perms[2];

struct Node {
  string type;
  int l, r;
  Node *left, *right;
  Node() {}
  int parse(int si, int at) {
    if (s[si][at] != '[') {
      if (s[si][at] == 'c') type = "concat";
      else if (s[si][at + 1] == 'h') type = "shuffle";
      else if (s[si][at + 1] == 'o') type = "sorted";

      at += type.length() + 1;
      l = lists[si].size();

      left = new Node();
      at = left->parse(si, at);
      at++;

      if (type == "concat") {
        right = new Node();
        at = right->parse(si, at);
        at++;
      }

      r = lists[si].size();
    }
    else {
      type = "list";
      string curr = "";
      at++;
      l = lists[si].size();
      while (s[si][at] != ']') {
        if (s[si][at] == ',') {
          lists[si].push_back(curr);
          curr = "";
        }
        else {
          curr += s[si][at];
        }
        at++;
      }
      lists[si].push_back(curr);
      r = lists[si].size();
      at++;
    }
    return at;
  }
};

bool custom_sort(const string &s1, const string &s2) {
  if (s1.length() != s2.length()) return s1.length() < s2.length();
  return s1 < s2;
}

void dfs(int si, Node * node) {
  if (node->type == "list") return;
  if (node->type == "shuffle") {
    string first = *(lists[si].begin() + node->l);
    auto st = lists[si].begin() + node->l;
    auto en = lists[si].begin() + node->r;
    int cnt = count(st, en, first);
    if (cnt != node->r - node->l) {
      sort(st, en, custom_sort);
      perms[si].push_back({node->l, node->r});
    }
  }
  else if (node->type == "sorted") {
    auto st = lists[si].begin() + node->l;
    auto en = lists[si].begin() + node->r;
    sort(st, en, custom_sort);
  }
  else dfs(si, node->left), dfs(si, node->right);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Node *root[2];
  for (int it = 0; it < 2; it++) {
    cin >> s[it];
    root[it] = new Node();
    root[it]->parse(it, 0);
    dfs(it, root[it]);
  }

  if (lists[0] == lists[1] and perms[0] == perms[1]) {
    cout << "equal\n";
  }
  else {
    cout << "not equal\n";
  }

  return 0;
}