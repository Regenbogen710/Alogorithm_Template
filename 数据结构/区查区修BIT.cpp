#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10;

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        f |= ch == '-';
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? -x : x;
}

inline void read(ll &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

void write(ll num) {
    if (num > 9)write(num / 10);
    putchar(num % 10 ^ 48);
}

ll n, m, root, mod, opt, x, y, z, u, v, w, t[N], t1[N];

inline void add(ll *t, ll pos, ll num) {
    for (ll i = pos; i <= n; i += i & -i)t[i] += num;
}

inline ll ask(ll *t, ll pos) {
    ll ans = 0;
    for (ll i = pos; i > 0; i -= i & -i)ans += t[i];
    return ans;
}

inline void modify(ll ql, ll qr, ll num) {
    ll l = min(ql, qr), r = max(ql, qr);
    add(t, l, num);
    add(t, r + 1, -num);
    add(t1, l, (l - 1) * num);
    add(t1, r + 1, -r * num);
}

inline ll query(ll ql, ll qr) {
    ll l = min(ql, qr), r = max(ql, qr);
    return r * ask(t, r) - ask(t1, r) - ((l - 1) * ask(t, l - 1) - ask(t1, l - 1));
}

int main() {
    read(n, m);
    for (ll i = 1; i <= n; i++)modify(i, i, read());
    for (ll i = 1; i <= m; i++) {
        read(opt);
        if (opt == 1) {
            read(u, v, w);
            modify(u, v, w);
        } else printf("%lld\n", query(read(), read()));
    }
    return 0;
}
