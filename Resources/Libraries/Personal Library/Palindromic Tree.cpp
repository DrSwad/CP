class PalindromicTree {
private:
  int A;
  string s;
  int last, ptr;
  vector<int> link, len, occ, depth;
  vector<vector<int>> nxt;

  void init(int sz) {
    link.resize(sz, 0), len.resize(sz, 0), occ.resize(sz, 0), depth.resize(sz, 0);
    nxt.resize(sz, vector<int>(A, 0));
    len[1] = -1, len[2] = 0, link[1] = link[2] = 1, last = ptr = 2;
  }

  void feed(int at) {
    while (s[at - len[last] - 1] != s[at]) last = link[last];
    int ch = s[at] - 'a', temp = link[last];
    while (s[at - len[temp] - 1] != s[at]) temp = link[temp];
    if (!nxt[last][ch]) {
      nxt[last][ch] = ++ptr, len[ptr] = len[last] + 2;
      link[ptr] = len[ptr] == 1 ? 2 : nxt[temp][ch];
      depth[ptr] = depth[link[ptr]] + 1;
      palindromes.emplace_back(at - len[ptr], at);
    }
    last = nxt[last][ch], ++occ[last];
  }

public:
  vector<pair<int, int>> palindromes;

  PalindromicTree(string s, int A = 26) {
    int n = s.length();
    this->s = '0' + s;
    this->A = A;
    init(n + 3);
    for (int i = 1; i <= n; ++i) feed(i);
  }
};