#include<bits/stdc++.h>
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

const ll N = 5e4 + 10, M = 1e5 + 10;
ll n, m, ned;
ll u[M], v[M], w[M], pos[M], type[M];
ll sum, ans, tot;

struct unionfind {
    ll fa[N];
    inline void init(ll n) { for (ll i = 0; i <= n; i++)fa[i] = i; }
    ll find(ll son) { return (fa[son] == son) ? son : fa[son] = find(fa[son]); }
    inline void setup(ll u, ll v) { fa[find(u)] = find(v); }
    inline bool query(ll u, ll v) { return find(u) == find(v); }
} uf;

inline bool cmp(ll i, ll j) {
    return w[i] < w[j] || (w[i] == w[j] && type[i] < type[j]);
}

void kruskal() {
    sum = 0, ans = 0, tot = 0, uf.init(n);
    sort(pos + 1, pos + 1 + m, cmp);
    for (ll ti = 1, i = pos[ti]; ti <= m && tot < n - 1; ti++, i = pos[ti]) {
        if (!uf.query(u[i], v[i])) {
            uf.setup(u[i], v[i]);
            if (!type[i])sum++;
            ans += w[i];
            tot++;
        }
    }
}

int main() {
    read(n, m, ned);
    for (ll i = 1; i <= m; i++)
        pos[i] = i;
    for (ll i = 1; i <= m; i++)
        read(u[i], v[i], w[i], type[i]);
    ll l = -114, r = 114, mid;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        for (ll i = 1; i <= m; i++)if (!type[i])w[i] += mid;
        kruskal();
        if (sum <= ned)r = mid - 1;
        else l = mid;
        for (ll i = 1; i <= m; i++)if (!type[i])w[i] -= mid;
    }
    if (sum <= ned) {
        mid--;
        for (ll i = 1; i <= m; i++)if (!type[i])w[i] += mid;
        kruskal();
        if (sum <= ned)r = mid - 1;
        else l = mid;
        for (ll i = 1; i <= m; i++)if (!type[i])w[i] -= mid;
    }
    printf("%lld", ans - mid * ned);
    return 0;
}
