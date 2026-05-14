#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10;
ll n, m, root, mod, opt, x, y, z, u, v;

inline ll read() {
    bool f = 0;
    ll x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        f |= ch == '-';
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? -x : x;
}

void write(ll num) {
    if (num > 9)write(num / 10);
    putchar(num % 10 ^ 48);
}

struct G {
    ll to[N], head[N], nxt[N], cnt;
    ll dfn[N], def[N], fa[N], size[N], maxson[N], top[N], dep[N], index;
    ll t[N], t1[N], val[N];

    inline void add(ll *t, ll pos, ll num) {
        for (ll i = pos; i <= n; i += i & -i) {
            t[i] += num;
            t[i] %= mod;
        }
    }

    inline ll ask(ll *t, ll pos) {
        ll ans = 0;
        for (ll i = pos; i > 0; i -= i & -i) {
            ans += t[i];
            ans += mod;
            ans %= mod;
        }
        return ans;
    }

    inline void modify(ll ql, ll qr, ll num) {
        ll l = min(ql, qr), r = max(ql, qr);
        add(t, l, num);
        add(t, r + 1, -num);
        add(t1, l, (l - 1) * num);
        add(t1, r + 1, -r * num);
    }

    inline ll query(ll ql, ll qr) {
        ll l = min(ql, qr), r = max(ql, qr);
        return r * ask(t, r) - ask(t1, r) + mod * 114514191 - ((l - 1) * ask(t, l - 1) - ask(t1, l - 1)) + mod;
    }

    inline void link(ll u, ll v) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    void dfs(ll now, ll anc, ll deep) {
        fa[now] = anc;
        dep[now] = deep;
        size[now] = 1;
        for (ll i = head[now]; i; i = nxt[i]) {
            if (to[i] != anc) {
                dfs(to[i], now, deep + 1);
                size[now] += size[to[i]];
                if (size[to[i]] > size[maxson[now]]) {
                    maxson[now] = to[i];
                }
            }
        }
    }

    void dfs2(ll now, ll topanc) {
        dfn[now] = ++index;
        top[now] = topanc;
        if (maxson[now]) {
            dfs2(maxson[now], topanc);
            for (ll i = head[now]; i; i = nxt[i]) {
                if (to[i] != fa[now] && to[i] != maxson[now]) {
                    dfs2(to[i], to[i]);
                }
            }
        }
    }

    inline ll queryPath(ll x, ll y) {
        ll u = x, v = y, res = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])swap(u, v);
            res += query(dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        res += query(dfn[v], dfn[u]);
        return res;
    }

    inline void modifyPath(ll x, ll y, ll num) {
        ll u = x, v = y;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])swap(u, v);
            modify(dfn[top[u]], dfn[u], num);
            u = fa[top[u]];
        }
        modify(dfn[v], dfn[u], num);
    }

    inline ll queryNode(ll now) {
        return query(dfn[now], dfn[now] + size[now] - 1);
    }

    inline void modifyNode(ll now, ll num) {
        modify(dfn[now], dfn[now] + size[now] - 1, num);
    }
} g;

int main() {
    n = read();
    m = read();
    root = read();
    mod = read();
    for (ll i = 1; i <= n; i++)g.val[i] = read();
    for (ll i = 1; i < n; i++) {
        u = read();
        v = read();
        g.link(u, v);
        g.link(v, u);
    }
    g.dfs(root, 0, 1);
    g.dfs2(root, root);
    for (ll i = 1; i <= n; i++)g.modifyPath(i, i, g.val[i]);
    for (ll i = 1; i <= m; i++) {
        opt = read();
        if (opt == 1) {
            x = read();
            y = read();
            z = read();
            g.modifyPath(x, y, z);
        } else if (opt == 2) {
            x = read();
            y = read();
            write(g.queryPath(x, y) % mod);
            putchar('\n');
        } else if (opt == 3) {
            x = read();
            y = read();
            g.modifyNode(x, y);
        } else {
            x = read();
            write(g.queryNode(x) % mod);
            putchar('\n');
        }
    }
    return 0;
}
