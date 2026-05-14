#include <bits/stdc++.h>

#define cbug(x) cerr<<"[ "<<(#x)<<" ]:"<<x<<" "<<"\n"
#define rep(i, l, r) for(ll i=(l);i<=(r);i++)
#define pre(i, r, l) for(ll i=(r);i>=(l);i--)
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

template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { x = x > y ? x : y; }

template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { x = x < y ? x : y; }

bool Memory_begin;
const ll N = 4e5 + 10, inf = 1e18;
ll n, m;
ll a[N], b[N];

const ll Node = N << 3;

struct line {
    ll k, b;
    inline line(ll _k = 0, ll _b = inf) { b = _b, k = _k; }
    inline ll operator [](const ll x) { return k * x + b; }
} val[Node];

ll trashnode[Node], top;
ll lson[Node], rson[Node], rt[N], cnt;

inline ll newnode() {
    if (!top)return ++cnt;
    else {
        ll now = trashnode[top--];
        lson[now] = rson[now] = 0;
        val[now] = line(0, inf);
        return now;
    }
}

#define mid ((l + r - ((l + r) < 0)) / 2)

void insert(ll &now, ll l, ll r, line L) {
    if (!now) now = newnode();
    if (val[now][mid] > L[mid])swap(L, val[now]);
    if (l == r)return void();
    if (val[now][l] > L[l])insert(lson[now], l, mid, L);
    if (val[now][r] > L[r])insert(rson[now], mid + 1, r, L);
}

void merge(ll &now, ll pre, ll l, ll r) {
    if (!now || !pre)return now = now + pre, void();
    insert(now, l, r, val[pre]);
    merge(lson[now], lson[pre], l, mid);
    merge(rson[now], rson[pre], mid + 1, r);
    if (!pre) trashnode[++top] = pre;
}

ll query(ll now, ll l, ll r, ll pos) {
    if (l == r || !now)return val[now][pos];
    if (pos <= mid)return min(val[now][pos], query(lson[now], l, mid, pos));
    else return min(val[now][pos], query(rson[now], mid + 1, r, pos));
}

ll ans[N];
vector<ll> G[N];

void dfs(ll now, ll fa) {
    for (const auto x: G[now]) {
        if (x == fa)continue;
        dfs(x, now);
        merge(rt[now], rt[x], -1e5, 1e5);
    }
    if (rt[now])ans[now] = query(rt[now], -1e5, 1e5, a[now]);
    insert(rt[now], -1e5, 1e5, line(b[now], ans[now]));
}

bool Memory_end;

int main() {
    //    freopen("1.in","r",stdin);
    //    freopen("2.out","w",stdout);
    read(n);
    rep(i, 1, n)read(a[i]);
    rep(i, 1, n)read(b[i]);
    for (ll i = 1; i < n; i++) {
        ll u = read(), v = read();
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(1, 0);
    rep(i, 1, n)printf("%lld ", ans[i]);
    //    fprintf(stderr, "%.3lf Ms\n", (clock()) / 1000.0);
    //    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    //    if ((&Memory_end - &Memory_begin) / 1048576.0 > 128)return fprintf(stderr, "MLE"), 0;
    return 0;
}

/*
Startx coding at 下午9:27
Finish debugging at
*/
