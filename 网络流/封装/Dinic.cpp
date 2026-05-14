#include<bits/stdc++.h>
#define rep(i,j,k) for(ll i=j;i<=k;i++)
using namespace std;
typedef long long ll;

struct Dinic {
    static const int N = 1e3 + 10, M = 2e4 + 10;
    static const ll INF = 0x3ffffffffff;
    int s, t;
    int to[M], nxt[M], pre[M], head[N], now[N], h[N], cnt;
    ll cap[M];

    void init(int sn, int tn) {
        s = sn; t = tn;
        memset(head, 0, sizeof(head));
        cnt = 0;
    }

    void add(int u, int v, ll w) {
        to[++cnt] = v; cap[cnt] = w; nxt[cnt] = head[u]; pre[cnt] = cnt + 1; head[u] = cnt;
        to[++cnt] = u; cap[cnt] = 0; nxt[cnt] = head[v]; pre[cnt] = cnt - 1; head[v] = cnt;
    }

    bool bfs() {
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

    ll dfs(ll u, ll flow) {
        if (u == t) return flow;
        ll ret = flow;
        for (ll i = now[u]; i && ret; i = nxt[i]) {
            now[u] = i;
            if (cap[i] && h[to[i]] == h[u] + 1) {
                ll temp = dfs(to[i], min(cap[i], ret));
                if (!temp) h[to[i]] = 0;
                ret -= temp; cap[i] -= temp; cap[pre[i]] += temp;
            }
        }
        return flow - ret;
    }

    ll maxflow() {
        ll mf = 0, temp;
        while (bfs()) while ((temp = dfs(s, INF))) mf += temp;
        return mf;
    }
};