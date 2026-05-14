#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
typedef long long ll;

struct MCMF {
    static const int N = 1e3 + 10, M = 2e5 + 10;
    static const ll INF = 0x7ffffffffff;
    int head[N], to[M], nxt[M], fri[M], cnt, s, t;
    ll cap[M], w[M];
    ll dis[N], pre[N], flow[N], pres[N];

    void init(int ns, int nt) {
        s = ns; t = nt;
        memset(head, 0, sizeof(head));
        cnt = 0;
    }

    void add(int u, int v, ll Cap, ll cost) {
        to[++cnt] = v; cap[cnt] = Cap; fri[cnt] = cnt + 1; w[cnt] = cost; nxt[cnt] = head[u]; head[u] = cnt;
        to[++cnt] = u; cap[cnt] = 0;   fri[cnt] = cnt - 1; w[cnt] = -cost; nxt[cnt] = head[v]; head[v] = cnt;
    }

    ll spfa() {
        memset(dis, 0x3f, sizeof dis);
        memset(pre, 0, sizeof pre);
        bitset<N> inq;
        deque<ll> q;
        q.emplace_front(s);
        flow[s] = INF; dis[s] = 0; inq[s] = 1;
        while (!q.empty()) {
            if (dis[q.back()] < dis[q.front()]) swap(q.back(), q.front());
            ll u = q.front(); q.pop_front();
            inq[u] = 0;
            for (ll i = head[u]; i; i = nxt[i]) {
                if (cap[i] > 0 && dis[to[i]] > dis[u] + w[i]) {
                    pre[to[i]] = u;
                    pres[to[i]] = i;
                    dis[to[i]] = dis[u] + w[i];
                    flow[to[i]] = min(flow[u], cap[i]);
                    if (!inq[to[i]]) {
                        if (!q.empty() && dis[to[i]] <= dis[q.front()]) q.emplace_front(to[i]);
                        else q.emplace_back(to[i]);
                        inq[to[i]] = 1;
                    }
                }
            }
        }
        return pre[t] != 0 ? flow[t] : -1;
    }

    pair<ll, ll> run() {
        ll mf = 0, cost = 0, pushed;
        while (~(pushed = spfa())) {
            ll u = t;
            while (u != s) {
                ll e = pres[u];
                cap[e] -= pushed;
                cap[fri[e]] += pushed;
                u = pre[u];
            }
            mf += pushed;
            cost += pushed * dis[t];
        }
        return {mf, cost};
    }
};