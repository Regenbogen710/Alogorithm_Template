// Created by regenbogen on 九月-02   and is--星期六
#include <bits/stdc++.h>
#include <bits/extc++.h>

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

ll Memory_begin;
const ll N = 2e5 + 10, T = 1e8;
ll n, m, head[N], to[N << 1], nxt[N << 1], w[N << 1], q[N], cnt, u, v, wei;
bitset<T> del, f;
bitset<N> ans;

inline void tlink(ll u, ll v, ll wei) {
    to[++cnt] = v;
    w[cnt] = wei;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

inline void link(ll u, ll v, ll wei) {
    tlink(u, v, wei), tlink(v, u, wei);
}

ll siz(ll now, ll fa) {
    ll res = 1;
    if (del[now])return 0;
    for (ll i = head[now]; i; i = nxt[i])if (to[i] != fa)res += siz(to[i], now);
    return res;
}


ll get_zx(ll now, ll fa, ll tot, ll &zx) {
    if (del[now])return 0;
    ll res = 1, maxson = 0;
    for (ll i = head[now]; i; i = nxt[i]) {
        if (to[i] != fa) {
            ll temp = get_zx(to[i], now, tot, zx);
            maxson = max(maxson, temp);
            res += temp;
        }
    }
    maxson = max(maxson, tot - res);
    if (maxson <= tot >> 1)zx = now;
    return res;
}

void get_dis(ll now, ll fa, ll dis, vector<ll> &x) {
    if (del[now]) return;
    if (dis > 1e7) return;
    x.emplace_back(dis);
    for (ll i = head[now]; i; i = nxt[i]) {
        if (to[i] != fa) {
            get_dis(to[i], now, dis + w[i], x);
        }
    }
}

void solve(ll now) {
    if (del[now])return void();
    get_zx(now, 0, siz(now, 0), now);
    del[now] = 1;
    vector<ll> cur;
    f[0] = 1;
    for (ll i = head[now]; i; i = nxt[i]) {
        vector<ll> dises;
        get_dis(to[i], now, w[i], dises);
        for (ll j = 1; j <= m; j++) {
            for (auto g: dises) {
                if (q[j] >= g) {
                    ans[j] = ans[j] | f[q[j] - g];
                }
            }
        }
        for (auto j: dises) {
            f[j] = 1;
            cur.emplace_back(j);
        }
    }
    for (auto i: cur)f[i] = 0;
    for (ll i = head[now]; i; i = nxt[i])solve(to[i]);
}

ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m);
    for (ll i = 1; i < n; i++) {
        read(u, v, wei);
        link(u, v, wei);
    }
    for (ll i = 1; i <= m; i++)read(q[i]);
    solve(1);
    for (ll i = 1; i <= m; i++)printf(ans[i] ? "AYE\n" : "NAY\n");
    //    fprintf(stderr, "%.3lf MB\n", -(&Memory_begin - &Memory_end) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start at下午5:07
//End at
