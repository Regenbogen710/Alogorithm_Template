#include<bits/stdc++.h>
#define max(a,b) (a<b)?b:a
using namespace std;
typedef long long ll;

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f |= ch == '-', ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); }
    return f ? -x : x;
}

template<typename T>
inline void read(T &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

const ll N = 3e5 + 10, M = 1e5 + 10;
ll n, k;

struct node {
    ll val, cnt;

    node() {
    }

    node(ll v, ll c) { val = v, cnt = c; }
    inline bool operator <(const node &cmp) const { return val < cmp.val || (val == cmp.val && cnt < cmp.cnt); }
    inline node operator +(const node &a) const { return node(val + a.val, cnt + a.cnt); }
    inline node operator +(const ll &a) const { return node(val + a, cnt); }
} f[N][3], base, d;

namespace G {
    const ll N = 3e5 + 10;
    ll head[N], to[N << 1], nxt[N << 1], w[N << 1], cnt;

    inline void tlink(ll u, ll v, ll wei) {
        to[++cnt] = v;
        w[cnt] = wei;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    inline void link(ll u, ll v, ll wei) { tlink(u, v, wei), tlink(v, u, wei); }

    void dpfs(ll now, ll fa) {
        memset(f[now], 0, sizeof(f[now]));
        f[now][2] = base;
        for (int i = head[now]; i; i = nxt[i]) {
            if (to[i] != fa) {
                dpfs(to[i], now);
                f[now][2] = max(f[now][2]+f[to[i]][0], f[now][1]+f[to[i]][1]+w[i]+base);
                f[now][1] = max(f[now][1]+f[to[i]][0], f[now][0]+f[to[i]][1]+w[i]);
                f[now][0] = max(f[now][0], f[now][0]+f[to[i]][0]);
            }
        }
        d = max(f[now][1]+base, f[now][2]);
        f[now][0] = max(f[now][0], d);
    }
}

ll u, v, w, l, r, mid;

int main() {
    read(n, k);
    for (ll i = 1; i < n; i++) {
        read(u, v, w);
        G::link(u, v, w);
    }
    l = -1e8, r = 1e8;
    ll ans = 0;
    while (l < r) {
        mid = (l + r) >> 1;
        base = node(mid, 1);
        G::dpfs(1, 1);
        if (f[1][0].cnt > k + 1)r = mid;
        else l = mid + 1;
    }
    base = node(l, 1);
    G::dpfs(1, 1);
    printf("%lld\n", f[1][0].val - l * (k + 1));
    return 0;
}
