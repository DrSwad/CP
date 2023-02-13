mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uid(0, (int)1e9);
auto gen = bind(uid, rng);
template<class T>
class implicit_treap {
  struct item {
    int prior, cnt;
    T value;
    bool rev;
    item *l, *r;
    item(T v) {
      value = v;
      rev = false;
      l = NULL;
      r = NULL;
      cnt = 1;
      prior = gen();
    }
  } *root, *node;
  int cnt(item * it) {
    return it ? it->cnt : 0;
  }
  void upd_cnt(item * it) {
    if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
  }
  void push(item * it) {
    if (it && it->rev) {
      it->rev = false;
      swap(it->l, it->r);
      if (it->l) it->l->rev ^= true;
      if (it->r) it->r->rev ^= true;
    }
  }
  void merge(item* &t, item * l, item * r) {
    push(l);
    push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->r, l->r, r),  t = l;
    else merge(r->l, l, r->l),  t = r;
    upd_cnt(t);
  }
  void split(item * t, item* &l, item* &r, int key, int add = 0) {
    if (!t) return void( l = r = 0 );
    push(t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key) split(t->l, l, t->l, key, add),  r = t;
    else split(t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt(t);
  }
  void insert(item* &t, item * element, int key) {
    item *l, *r;
    split(t, l, r, key);
    merge(l, l, element);
    merge(t, l, r);
    l = NULL;
    r = NULL;
  }
  T elementAt(item* &t, int key) {
    push(t);
    T ans;
    if (cnt(t->l) == key) ans = t->value;
    else if (cnt(t->l) > key) ans = elementAt(t->l, key);
    else ans = elementAt(t->r, key - 1 - cnt(t->l));
    return ans;
  }
  void erase(item* &t, int key) {
    push(t);
    if (!t) return;
    if (key == cnt(t->l)) merge(t, t->l, t->r);
    else if (key < cnt(t->l)) erase(t->l, key);
    else erase(t->r, key - cnt(t->l) - 1);
    upd_cnt(t);
  }
  void reverse(item* &t, int l, int r) {
    item *t1, *t2, *t3;
    split(t, t1, t2, l);
    split(t2, t2, t3, r - l + 1);
    t2->rev ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
  }
  void cyclic_shift(item* &t, int L, int R) {
    if (L == R) return;
    item *l, *r, *m;
    split(t, t, l, L);
    split(l, l, m, R - L + 1);
    split(l, l, r, R - L);
    merge(t, t, r);
    merge(t, t, l);
    merge(t, t, m);
    l = NULL;
    r = NULL;
    m = NULL;
  }
  void output(item * t, vector<T> &arr) {
    if (!t) return;
    push(t);
    output(t->l, arr);
    arr.push_back(t->value);
    output(t->r, arr);
  }
public:
  implicit_treap() {
    root = NULL;
  }
  void insert(T value, int position) {
    node = new item(value);
    insert(root, node, position);
  }
  void erase(int position) {
    erase(root, position);
  }
  void reverse(int l, int r) { // [l, r]
    reverse(root, l, r);
  }
  T elementAt(int position) {
    return elementAt(root, position);
  }
  void cyclic_shift(int L, int R) {
    cyclic_shift(root, L, R);
  }
  int size() {
    return cnt(root);
  }
  void output(vector<T> &arr) {
    output(root, arr);
  }
};
// All indices 0-indexed