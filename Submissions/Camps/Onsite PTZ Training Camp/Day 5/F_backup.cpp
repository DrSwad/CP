ll solve(int n, ll pos_i, ll pos_j, ll val, ll a, ll b) {
  if (pos_i > pos_j) swap(pos_i, pos_j);
  ll ret = 0;
  for (ll m = 0; pos_j <= b; m++, pos_i += n, pos_j += n, val += n) {
    if (a <= pos_i and pos_j <= b) {
      ret += val * (pos_i - a + 1) * (b - pos_j + 1);
    }
  }
  return ret;
}