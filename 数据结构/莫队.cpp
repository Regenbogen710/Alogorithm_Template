//Creat by regenbogen at 2023/9/22/9:45
//星期五

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
ll n, a[N], ans[N], pos[N], m, ql[N], qr[N], A[N], B[N], bl[N], Block, ans1[N], ans2[N], vis[N];
ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m);
    Block = sqrt(n);
    rep(i, 1, n)read(a[i]), bl[i] = i / Block;
    rep(i, 1, m) {
        read(ql[i], qr[i], A[i], B[i]);
        pos[i] = i;
    }
    sort(pos + 1, pos + 1 + m, [&](const ll &i, const ll &j) {
        return (bl[ql[i]] ^ bl[ql[j]]) ? bl[ql[i]] < bl[ql[j]] : (bl[ql[i]] & 1) ? qr[i] < qr[j] : qr[i] > qr[j];
    });
    ll l = 1, r = 0;
    rep(I, 1, m) {
        ll i = pos[I];
        while (r < qr[i])vis[a[++r]]++;
        while (l > ql[i])vis[a[--l]]++;
        while (r > qr[i])vis[a[r--]]--;
        while (l < ql[i])vis[a[l++]]--;
        rep(j, A[i], B[i]) {
            ans1[i] += vis[j];
            ans2[i] += (bool) vis[j];
        }
    }
    rep(i, 1, m)printf("%lld %lld\n", ans1[i], ans2[i]);
    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start coding at 9:45
//Finish debugging at
