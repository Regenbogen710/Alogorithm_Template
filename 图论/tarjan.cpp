// #pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 10, M = 2e5 + 10, mod = 1e9 + 7;
ll n, m, u, v, cnt, res[N], tot;

struct G {
    ll head[N], nxt[M], to[M], cnt, u, v, w, n, m, sum;
    ll low[N], dfn[N], index, con[N], tot;
    bitset<N> cut;

    void link(ll u, ll v) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    void init() {
        scanf("%lld %lld", &n, &m);
        for (ll i = 1; i <= m; i++) {
            scanf("%lld %lld", &u, &v);
            link(u, v);
            link(v, u);
        }
    }

    void tarjan(ll now, ll root) {
        ll son = 0;
        dfn[now] = low[now] = ++index;
        for (ll i = head[now]; i; i = nxt[i]) {
            if (!dfn[to[i]]) {
                son++;
                tarjan(to[i], root);
                low[now] = min(low[now], low[to[i]]);
                if (low[to[i]] >= dfn[now] && now != root && !cut[now])cut[now] = 1, sum++;
            } else {
                low[now] = min(low[now], dfn[to[i]]);
            }
        }
        if (now == root && son > 1 && !cut[now])cut[now] = 1, sum++;
        return;
    }
} g;

int main() {
    g.init();
    for (ll i = 1; i <= g.n; i++)if (!g.dfn[i])g.tarjan(i, i);
    printf("%lld\n", g.sum);
    for (ll i = 1; i <= g.n; i++)if (g.cut[i])printf("%lld ", i);
    return 0;
}
