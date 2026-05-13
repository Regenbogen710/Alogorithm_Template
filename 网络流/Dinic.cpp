#include<bits/stdc++.h>
#define rep(i,j,k) for(ll i=j;i<=k;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

namespace F {
    const ll N = 1e3 + 10, M = 2e4 + 10, INF = 0x3ffffffffff;
    ll s, t, n, m, to[M], nxt[M], cap[M], pre[M], head[N], h[N], now[N], cnt;

    void setup(ll sn, ll tn) {
        s = sn;
        t = tn;
    }

    void tlink(ll u, ll v, ll wei, ll fir) {
        to[++cnt] = v;
        cap[cnt] = wei;
        nxt[cnt] = head[u];
        pre[cnt] = fir;
        head[u] = cnt;
    }

    void link(ll u, ll v, ll w) {
        tlink(u, v, w, cnt + 2);
        tlink(v, u, 0, cnt);
    }

    bool bfs() {
        queue<ll> q;
        q.emplace(s);
        memset(h, 0, sizeof(h));
        h[s] = 1;
        now[s] = head[s];
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            if (u == t)return true;
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
        if (u == t)return flow;
        ll ret = flow;
        for (ll i = now[u]; i && ret; i = nxt[i]) {
            now[u] = i;
            if (cap[i] && h[to[i]] == h[u] + 1) {
                ll temp = dfs(to[i], (cap[i] < ret) ? cap[i] : ret);
                if (!temp)h[to[i]] = 0;
                ret -= temp;
                cap[i] -= temp, cap[pre[i]] += temp;
            }
        }
        return flow - ret;
    }

    ll solve() {
        ll maxflow = 0, temp = 0;
        while (bfs())while (temp = dfs(s, INF))maxflow += temp;
        return maxflow;
    }
}

ll n, m, s, t, u, v, w;

int main() {
    scanf("%lld %lld %lld %lld\n", &n, &m, &s, &t);
    F::setup(s, t);
    rep(i, 1, m) {
        scanf("%lld %lld %lld", &u, &v, &w);
        F::link(u, v, w);
    }
    printf("%lld", F::solve());
    return 0;
}
