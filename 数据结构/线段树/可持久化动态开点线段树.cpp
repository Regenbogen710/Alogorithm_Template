//Creat by regenbogen at 2023/9/19/17:58
//星期二
#pragma GCC optimize(2)
#include <bits/stdc++.h>

#define rep(i, l, r) for(int i=(l);i<=(r);i++)
#define pre(i, r, l) for(int i=(r);i>=(l);i--)

using namespace std;
typedef long long ll;

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f |= ch == '-', ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); }
    return f ? -x : x;
};

template<typename T>
inline void read(T &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { if (x < y)x = y; }

template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { if (x > y)x = y; }

ll Memory_begin;
const ll N = 1e6 + 10, mod = 998244353;
ll n, m, l, r, x, now;

struct chairtree {
    ll ch[2][N << 5], sum[N << 5], tag[N << 5], rt[N], cnt;
#define lson(now) ch[0][now]
#define rson(now) ch[1][now]

    inline ll newnode(ll pre = 0) {
        cnt++;
        ch[1][cnt] = ch[1][pre];
        ch[0][cnt] = ch[0][pre];
        sum[cnt] = sum[pre];
        tag[cnt] = tag[pre];
        return cnt;
    }

    inline void pushup(ll now) {
        sum[now] = sum[lson(now)] + sum[rson(now)];
    }

    void buildpre(ll &now, ll l, ll r) {
        now = newnode();
        if (l == r) {
            read(sum[now]);
            return;
        }
        ll mid = (l + r) >> 1;
        buildpre(lson(now), l, mid);
        buildpre(rson(now), mid + 1, r);
        pushup(now);
    }

    void modifypre(ll &now, ll pre, ll ql, ll qr, ll l, ll r, ll x) {
        if (ql > r || qr < l)return;
        now = newnode(pre);
        sum[now] += x * (min(qr, r) - max(ql, l) + 1);
        if (ql <= l && r <= qr) {
            tag[now] += x;
            return;
        }
        ll mid = (l + r) >> 1;
        modifypre(lson(now), lson(pre), ql, qr, l, mid, x);
        modifypre(rson(now), rson(pre), ql, qr, mid + 1, r, x);
    }

    ll querypre(ll now, ll ql, ll qr, ll l, ll r) {
        if (qr < l || ql > r)return 0;
        if (ql <= l && r <= qr)return sum[now];
        ll mid = (l + r) >> 1;
        return (querypre(lson(now), ql, qr, l, mid) +
                querypre(rson(now), ql, qr, mid + 1, r) +
                (min(qr, r) - max(ql, l) + 1) * tag[now]);
    }

    inline ll query(ll now, ll ql, ll qr) { return querypre(rt[now], ql, qr, 1, n); }
    inline void modify(ll now, ll pre, ll l, ll r, ll x) { modifypre(rt[now], rt[pre], l, r, 1, n, x); }
    inline void build() { buildpre(rt[0], 1, n); }

#undef lson
#undef rson
} seg;

inline char fetch() {
    char ch = getchar();
    while (ch < 'A' || ch > 'Z')ch = getchar();
    return ch;
}

ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m);
    seg.build();
    rep(i, 1, m) {
        char opt = fetch();
        if (opt == 'Q') {
            read(l, r);
            printf("%lld\n", seg.query(now, l, r));
        } else if (opt == 'C') {
            now++;
            read(l, r, x);
            seg.modify(now, now - 1, l, r, x);
        } else if (opt == 'H') {
            read(l, r, x);
            printf("%lld\n", seg.query(x, l, r));
        } else if (opt == 'B') {
            read(now);
        }
    }
    //    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start coding at 17:58
//Finish debugging at 21:27
