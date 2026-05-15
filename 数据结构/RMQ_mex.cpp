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
const ll N = 2e5 + 10, mod = 998244353, inf = 0x3ffffffffff;
ll n, ql, qr, a[N], m, rt[N];

struct chairtree {
    ll ch[N << 5][2], val[N << 5], cnt;
    inline ll newnode() { return ++cnt; }

    void modifypre(ll pre, ll &now, ll l, ll r, ll pos, ll x) {
        if (l > pos || r < pos)return;
        now = newnode();
        ch[now][1] = ch[pre][1];
        ch[now][0] = ch[pre][0];
        val[now] = inf;
        if (l == r)return val[now] = x, void();
        ll mid = (l + r) >> 1;
        modifypre(ch[pre][0], ch[now][0], l, mid, pos, x);
        modifypre(ch[pre][1], ch[now][1], mid + 1, r, pos, x);
        val[now] = min(val[ch[now][0]], val[ch[now][1]]);
    }

    ll querypre(ll now, ll l, ll r, ll pos) {
        if (l == r)return l;
        ll mid = (l + r) >> 1;
        if (val[ch[now][0]] < pos)return querypre(ch[now][0], l, mid, pos);
        else return querypre(ch[now][1], mid + 1, r, pos);
    }

    inline void modify(ll pre, ll now, ll pos, ll x) { modifypre(rt[pre], rt[now], 0, 2e5, pos, x); }
    inline ll query(ll ver, ll pos) { return querypre(rt[ver], 0, 2e5, pos); }
} tree;

ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m);
    rep(i, 1, n)tree.modify(i - 1, i, read(), i);
    rep(i, 1, m) {
        read(ql, qr);
        printf("%lld\n", tree.query(qr, ql));
    }
    //    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start at下午1:35
//End at
