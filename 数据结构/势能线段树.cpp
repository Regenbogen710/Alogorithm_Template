#include <bits/stdc++.h>

#define cbug(x) cerr<<"< "<<(#x)<<":"<<x<<" >"<<"\n"
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
const ll N = 2e5 + 10;
ll n, m;
const ll Node = N << 3;
#define lson (now << 1)
#define rson (now << 1 | 1)
#define div(a,b) (ll)floor((double)(a)/(double)(b))

ll sum[Node], Min[Node], Max[Node], tag[Node];

inline void add(ll now, ll x, ll l, ll r) {
    Max[now] += x;
    Min[now] += x;
    sum[now] += (r - l + 1) * x;
    tag[now] += x;
}

inline void pushdown(ll now, ll l, ll r) {
    ll mid = (l + r) >> 1;
    if (tag[now]) {
        add(lson, tag[now], l, mid);
        add(rson, tag[now], mid + 1, r);
        tag[now] = 0;
    }
}

inline void pushup(ll now) {
    sum[now] = sum[lson] + sum[rson];
    Max[now] = max(Max[lson], Max[rson]);
    Min[now] = min(Min[lson], Min[rson]);
}

void build(ll now, ll l, ll r) {
    if (l == r)return add(now, read(), l, r);
    ll mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(now);
}

void modify(ll now, ll l, ll r, ll ql, ll qr, ll opt, ll x) {
    if (ql > r || qr < l)return;
    if (ql <= l && r <= qr) {
        if (opt == 0 && (Max[now] - div(Max[now], x)) == (Min[now] - div(Min[now], x)))return add(
            now, div(Max[now], x) - Max[now], l, r);
        if (opt == 1) return add(now, x, l, r);
    }
    pushdown(now, l, r);
    ll mid = (l + r) >> 1;
    modify(lson, l, mid, ql, qr, opt, x);
    modify(rson, mid + 1, r, ql, qr, opt, x);
    pushup(now);
}

ll querysum(ll now, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l)return 0;
    if (ql <= l && r <= qr)return sum[now];
    pushdown(now, l, r);
    ll mid = (l + r) >> 1;
    return querysum(lson, l, mid, ql, qr) + querysum(rson, mid + 1, r, ql, qr);
}


ll querymin(ll now, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l)return 1e16;
    if (ql <= l && r <= qr)return Min[now];
    pushdown(now, l, r);
    ll mid = (l + r) >> 1;
    return min(querymin(lson, l, mid, ql, qr), querymin(rson, mid + 1, r, ql, qr));
}

bool Memory_end;


int main() {
    //    freopen("market.in", "r", stdin);
    //    freopen("market.out", "w", stdout);
    read(n, m);
    build(1, 1, n);
    rep(i, 1, m) {
        ll opt = read(), l = read() + 1, r = read() + 1;
        if (opt == 1)modify(1, 1, n, l, r, 1, read());
        if (opt == 2)modify(1, 1, n, l, r, 0, read());
        if (opt == 3)printf("%lld\n", querymin(1, 1, n, l, r));
        if (opt == 4)printf("%lld\n", querysum(1, 1, n, l, r));
    }
    //    fprintf(stderr, "%.3lf Ms\n", (clock()) / 1000.0);
    //    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    //    if ((&Memory_end - &Memory_begin) / 1048576.0 > 128)return fprintf(stderr, "MLE"), 0;
    return 0;
}

/*
Start coding at 上午10:20
Finish debugging at
*/
