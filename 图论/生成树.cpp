#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

inline void read(ll &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

namespace unionfind {
    const ll N = 5e3 + 10;
    ll fa[N];
    inline void init(ll n) { for (ll i = 1; i <= n; i++)fa[i] = i; }
    ll find(ll son) { return (fa[son] == son) ? son : find(fa[son]); }
    inline void setup(ll u, ll v) { fa[find(u)] = find(v); }
    inline bool query(ll u, ll v) { return find(u) == find(v); }
}

const ll M = 2e5 + 10;
ll n, m, ans, cnt;
ll u[M], v[M], w[M], pos[M], vis[M];

int main() {
    read(n, m);
    unionfind::init(n);
    for (ll i = 1; i <= m; i++)pos[i] = i;
    for (ll i = 1; i <= m; i++)read(u[i], v[i], w[i]);
    sort(pos + 1, pos + 1 + m, [&](ll i, ll j) { return w[i] < w[j]; });
    for (ll i = 1, tot = 0; i <= m && tot + 1 < n; i++) {
        if (!unionfind::query(u[pos[i]], v[pos[i]])) {
            unionfind::setup(u[pos[i]], v[pos[i]]);
            ans += w[pos[i]];
            tot++;
        }
    }
    for (ll i = 1; i <= n; i++) {
        if (!vis[unionfind::find(i)]) {
            cnt++;
            vis[unionfind::find(i)] = 1;
        }
    }
    if (cnt > 1)return printf("orz"), 0;
    printf("%lld", ans);
    return 0;
}
