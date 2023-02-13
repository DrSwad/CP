const int MAX = 1e5 + 5, ALPHA = 10; // total characters, alphabet size
const char START = '0'; // first letter in alphabet
 
inline scale(char c){ return c - START; }

struct Trie {
  int root, nodes, nxt[MAX][ALPHA], finished[MAX];
 
  Trie(){
    root = nodes = 1;
    memset(nxt, 0, sizeof nxt);
  }
 
  void insert(string s){
    int cur = root;
    for(auto c : s){
      if(!nxt[cur][scale(c)]) nxt[cur][scale(c)] = ++nodes;
      cur = nxt[cur][scale(c)];
    }
    finished[cur]++;
  }
 
  bool find(string s){
    int cur = root;
    for(auto c : s){
      if(!nxt[cur][scale(c)]) return false;
      cur = nxt[cur][scale(c)];
    }
    return finished[cur];
  }
 
  void erase(string s){ // may need to call find() before
    int cur = root;
    for(auto c : s) cur = nxt[cur][scale(c)];
    finished[cur]--;
  }
};