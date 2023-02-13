//1-based

void update(int n, int idx, int v){
  while(id <= n) tree[idx] += v, idx += idx & (-idx);
}

int query(int id){
  int sum = 0;
  while(idx > 0) sum += tree[idx], idx -= idx & (-idx);
  return sum;
}
