#include<bits/stdc++.h>
#define rep(i,j,k) for(ll i=j;i<=k;i++)
using namespace std;
typedef long long ll;

struct BoundFlow {
    static const int N = 1e3 + 10, M = 2e5 + 10;
    static const ll INF = 0x3ffffffffff;
    int head[N], to[M], nxt[M], pre[M], now[N], h[N], cnt;
    ll cap[M];
    ll balance[N], sum_need;

    void clear() {
        memset(head, 0, sizeof(head));
        memset(balance, 0, sizeof(balance));
        cnt = 0; sum_need = 0;
    }

    void addEdge(int u, int v, ll l, ll r) {
        balance[u] -= l; balance[v] += l;
        to[++cnt] = v; cap[cnt] = r - l; nxt[cnt] = head[u]; pre[cnt] = cnt + 1; head[u] = cnt;
        to[++cnt] = u; cap[cnt] = 0;      nxt[cnt] = head[v]; pre[cnt] = cnt - 1; head[v] = cnt;
    }

    bool bfs(int s, int t) {
        queue<ll> q; q.emplace(s);
        memset(h, 0, sizeof(h));
        h[s] = 1; now[s] = head[s];
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            if (u == t) return true;
            for (ll i = head[u]; i; i = nxt[i]) {
                if (cap[i] && !h[to[i]]) {
                    now[to[i]] = head[to[i]];
                    h[to[i]] = h[u] + 1;
                    q.emplace(to[i]);
                }
            }
        }
        return false;
    }

    ll dfs(int s, int t, ll u, ll flow) {
        if (u == t) return flow;
        ll ret = flow;
        for (ll i = now[u]; i && ret; i = nxt[i]) {
            now[u] = i;
            if (cap[i] && h[to[i]] == h[u] + 1) {
                ll temp = dfs(s, t, to[i], min(cap[i], ret));
                if (!temp) h[to[i]] = 0;
                ret -= temp; cap[i] -= temp; cap[pre[i]] += temp;
            }
        }
        return flow - ret;
    }

    ll maxFlow(int s, int t) {
        ll mf = 0, temp;
        while (bfs(s, t)) while ((temp = dfs(s, t, s, INF))) mf += temp;
        return mf;
    }

    bool feasible(int n) { // 无源汇可行流
        int S = n + 1, T = n + 2;
        sum_need = 0;
        for (int i = 1; i <= n; ++i) {
            if (balance[i] > 0) {
                addEdge(S, i, 0, balance[i]);  // 下界0，上界balance[i]
                sum_need += balance[i];
            } else if (balance[i] < 0) {
                addEdge(i, T, 0, -balance[i]);
            }
        }
        return maxFlow(S, T) == sum_need;
    }

    ll feasible(int n, int s, int t) { // 有源汇可行流，返回可行流流量，不可行返回 -1
        int S = n + 1, T = n + 2;
        // 构建平衡边
        sum_need = 0;
        for (int i = 1; i <= n; ++i) {
            if (balance[i] > 0) {
                addEdge(S, i, 0, balance[i]);
                sum_need += balance[i];
            } else if (balance[i] < 0) {
                addEdge(i, T, 0, -balance[i]);
            }
        }
        // 添加 t->s 容量 INF 的边
        addEdge(t, s, 0, INF);
        if (maxFlow(S, T) != sum_need) return -1;
        // 找到 t->s 的边并返回正向边已流的流量
        for (int i = head[t]; i; i = nxt[i])
            if (to[i] == s) return cap[pre[i]];
        return -1;
    }

    ll maxFlowBound(int n, int s, int t) {
        ll base = feasible(n, s, t);
        if (base == -1) return -1;
        return maxFlow(s, t);
    }

    ll minFlowBound(int n, int s, int t) {
        ll base = feasible(n, s, t);
        if (base == -1) return -1;
        // 删除 t->s 的 INF 边
        for (int i = head[t]; i; i = nxt[i])
            if (to[i] == s) {
                cap[i] = 0; cap[pre[i]] = 0;
                break;
            }
        ll backFlow = maxFlow(t, s);
        return base - backFlow;
    }
};