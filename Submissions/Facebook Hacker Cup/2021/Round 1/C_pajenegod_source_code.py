import sys
from collections import defaultdict
input = raw_input 
MOD = 10**9 + 7
 
def exclusive(A, base, f, node):
    n = len(A)
 
    B = [base] * n
    for bit in reversed(range(n.bit_length())):
        for i in reversed(range(n)):
            B[i] = B[i // 2]
        for i in range(n & ~(bit == 0)):
            ind = (i >> bit) ^ 1
            B[ind] = f(B[ind], A[i], node, i)
    return B
 
def rerooter(graph, A, f = lambda a,b,node,eind: a + b, g = lambda x,node: x):
    n = len(graph)
    rootDP = list(A)
    edgeDP = [[]] * n
 
    P = [-1] * n
    P[0] = 0
    bfs = [0]
    for node in bfs:
        for nei in graph[node]:
            if P[nei] == -1:
                P[nei] = node
                bfs.append(nei)
 
    DP = list(A)
    for node in reversed(bfs):
        for eind, nei in enumerate(graph[node]):
            if P[node] != nei:
                DP[node] = f(DP[node], DP[nei], node, eind)
        DP[node] = g(DP[node], node)
    
    for node in bfs:
        DP[P[node]] = DP[node]
        DPvec = [DP[nei] for nei in graph[node]]
        edgeDP[node] = DPvec
 
        DPexcl_vec = exclusive(DPvec, A[node], f, node)
        for nei, dp in zip(graph[node], DPexcl_vec):
            DP[nei] = g(dp, node)
        rootDP[node] = g(f(DPexcl_vec[0], DPvec[0], node, 0), node)
    return rootDP, edgeDP


inp = [int(x) for x in sys.stdin.read().split()]; ii = 0

t = inp[ii]; ii += 1
for cas in range(t):
    n = inp[ii]; ii += 1
    coupl = [[] for _ in range(n)]
    C = [[] for _ in range(n)]
    edge_indexer = [[] for _ in range(n)]
    
    for _ in range(n - 1):
        u = inp[ii] - 1; ii += 1
        v = inp[ii] - 1; ii += 1
        c = inp[ii]; ii += 1
        
        edge_indexer[u].append(len(coupl[v]))
        edge_indexer[v].append(len(coupl[u]))

        coupl[u].append(v)
        coupl[v].append(u)
        C[u].append(c)
        C[v].append(c)
        
    DP = [(0,)*20 + (1,) for _ in range(n)]

    def f(DPnode, DPchild, node, eind):
        c = C[node][eind]
        
        ret = list(DPnode)
        ret[0] += DPchild[0]

        for i in range(1, 21):
            for j in range(1, 21):
                ret[0] += DPnode[i] * DPchild[j] % MOD * min(i,j,c)

        for j in range(1, 21):
            ret[min(c, j)] += DPchild[j]

        for i in range(21):
            ret[i] %= MOD

        return tuple(ret)
    
    DP, edgeDP = rerooter(coupl, DP, f)

    ans = 1 if n > 2 else 0
    for node in range(n):
        for eind, nei in enumerate(coupl[node]):
            if node < nei:
                nei_eind = edge_indexer[node][eind]
                ans = ans * (edgeDP[node][eind][0] + edgeDP[nei][nei_eind][0]) % MOD

    print 'Case #%d: %d' % (cas + 1, ans)
