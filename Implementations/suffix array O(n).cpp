/***
    * scan sa::str
    * n = strlen(sa::str)
    * call sa::build(n)

    * there are n+1 suffixes including the null suffix(denoted as n'th suffix, 0 based suffix indexing)
    * S[0 ... n] is the suffix array ( n+1 elements including the null suffix )
    * null suffix will be in the 0'th position of S
    * rnk[i] denotes the index of the i'th suffix in S[]
    * lcp[0] = 0, lcp[i] = longest commong prefix( suffix S[i-1], suffix S[i] )
***/

namespace sa {
    const int N = 100010; /// maximum possible string size

    char str[N];
    int wa[N], wb[N], wv[N], wc[N];
    int r[N], S[N], rnk[N], lcp[N];


    int cmp(int *r, int a, int b, int l) {
        return r[a] == r[b] && r[a + l] == r[b + l];
    }

    void da(int *r, int *sa, int n, int m) {
        int i, j, p, *x = wa, *y = wb, *t;
        for(i = 0; i < m; i++) wc[i] = 0;
        for(i = 0; i < n; i++) wc[x[i] = r[i]]++;
        for(i = 1; i < m; i++) wc[i] += wc[i - 1];
        for(i = n - 1; i >= 0; i--) S[--wc[x[i]]] = i;
        for(j = 1, p = 1; p < n; j *= 2, m = p) {
            for(p = 0, i = n - j; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(S[i] >= j) y[p++] = S[i] - j;
            for(i = 0; i < n; i++) wv[i] = x[y[i]];
            for(i = 0; i < m; i++) wc[i] = 0;
            for(i = 0; i < n; i++) wc[wv[i]] ++;
            for(i = 1; i < m; i++) wc[i] += wc[i - 1];
            for(i = n - 1; i >= 0; i--) S[--wc[wv[i]]] = y[i];
            for(t = x, x = y, y = t, p = 1, x[S[0]] = 0, i = 1; i < n; i++) x[S[i]]= cmp(y, S[i - 1], S[i], j) ? p - 1 : p++;
        }
    }

    void calheight(int *r, int *sa, int n) {
        int i, j, k = 0;
        for(i = 1; i <= n; i++) rnk[S[i]] = i;
        for(i = 0; i < n; lcp[rnk[i++]] = k ) {
            for(k ? k-- : 0, j = S[rnk[i]-1]; r[i+k] == r[j+k]; k++);
        }
    }

    void build(int n) {
        for(int i = 0; str[i]; i++) r[i] = (int)str[i]; // or do some scaling
        r[n] = 0;
        da(r, S, n+1, 128); // 128 -> maximum possible asci value of a character + 1
        calheight(r, S, n);
    }
}
