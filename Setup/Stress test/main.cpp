#include <bits/stdc++.h>
using namespace std;

int query(int at) {
    cout << "? " << at << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int ans) {
    cout << "! " << ans << endl;
    exit(EXIT_SUCCESS);
}

void go(int L, int R) {
    if (L == R) answer(L);

    assert(R - L >= 2);

    int mid = (L + R) / 2;

    int l = query(mid - 1);
    int m = query(mid);
    int r = query(mid + 1);

    if (m < l && m < r) answer(mid);

    if (l < m) go(L, mid);
    else go(mid, R);
}

int main() {
    int n;
    cin >> n;

    if (n == 1) answer(1);

    if (query(1) < query(2)) answer(1);
    else if (query(n) < query(n - 1)) answer(n);
    else go(1, n);

    return 0;
}