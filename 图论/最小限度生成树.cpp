#include<bits/stdc++.h>
// #define fastread
#define rep(i,l,r) for(ll i=(l);i<=(r);i++)
#define pre(i,r,l) for(ll i=(r);i>=(l);i--)
using namespace std;
typedef int ll;
typedef long long lll;
#ifdef fastread
char *p1, *p2, buf[1 << 22];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2)?EOF:*p1++)
#endif
inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f = ch == '-', ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); }
    return f ? -x : x;
}

template<typename T>
inline void read(T &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) { read(x), read(args...); }

template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { if (x < y)x = y; }

template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { if (x > y)x = y; }

ll Memory_begin;
const ll N = 5e4 + 10, M = 5e5 + 10, mod = 998244353;
ll n, m, s, k, u[M], v[M], w[M], pos[M], ans, anc;
ll res, val, cnt, p0[M], ps[M], n0, ns;
bitset<N> vis;

struct unionfind {
    ll fa[N];

    unionfind() {
        rep(i, 0, n)fa[i] = i;
    }

    ll find(ll son) { return son == fa[son] ? son : fa[son] = find(fa[son]); }
    inline void setup(ll u, ll v) { fa[find(u)] = find(v); }
    inline bool query(ll u, ll v) { return find(u) == find(v); }
};

inline void mergesort(ll x) {
    ll cnt = 1, i = 1, j = 1;
    while (i <= n0 && j <= ns) {
        if (w[ps[j]] + x < w[p0[i]])pos[cnt++] = ps[j++];
        else pos[cnt++] = p0[i++];
    }
    while (i <= n0)pos[cnt++] = p0[i++];
    while (j <= ns)pos[cnt++] = ps[j++];
}

inline void check(ll x) {
    unionfind z;
    mergesort(x);
    res = 0, val = 0, cnt = 0;
    rep(j, 1, m) {
        ll i = pos[j];
        if (!z.query(u[i], v[i])) {
            cnt++, val += w[i];
            z.setup(u[i], v[i]);
            if (u[i] == s || v[i] == s)res++, val += x;
        }
        if (cnt == n - 1)break;
    }
}

ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m, s, k);
    unionfind e;
    rep(i, 1, m) {
        read(u[i], v[i], w[i]);
        if (u[i] == s || v[i] == s)ps[++ns] = i;
        else p0[++n0] = i, e.setup(u[i], v[i]);
    }
    ll temp = 0;
    rep(i, 2, n) {
        if (!vis[e.find(i)]) {
            temp++, vis[e.find(i)] = 1;
        }
    }
    if (ns < k || temp > k) {
        printf("Impossible");
        return 0;
    }
    sort(p0 + 1, p0 + 1 + n0, [&](ll i, ll j) { return w[i] < w[j]; });
    sort(ps + 1, ps + 1 + ns, [&](ll i, ll j) { return w[i] < w[j]; });
    ll l = -3e4 + 10, r = 3e4 + 10, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        check(mid);
        if (res <= k) r = mid;
        else l = mid + 1;
    }
    check(l);
    printf("%lld ", val - l * k);
    fprintf(stderr, "\n%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}
