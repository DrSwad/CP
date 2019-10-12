int lca(int u, int v) {
    if (lv[u] < lv[v]) {
        swap(u, v);
    }
    for (int i = LOGN - 1; i >= 0; i--) {
        if (lv[u] - (1 << i) >= lv[v]) {
            u = P[i][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOGN - 1; i >= 0; i--) {
        if (P[i][u] != P[i][v]) {
            u = P[i][u];
            v = P[i][v];
        }
    }
    return par[u];
}