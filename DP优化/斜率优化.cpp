//Created by regenbogen on 23-8-25.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3e5 + 10;
ll c[N], t[N], n, s, f[N], q[N], qh = 1, qt = 1;
ll k(ll u) { return t[u] + s; }
ll x(ll u) { return c[u]; }
ll y(ll u) { return f[u]; }

int main() {
    scanf("%lld%lld", &n, &s);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld %lld", &t[i], &c[i]);
        c[i] += c[i - 1];
        t[i] += t[i - 1];
    }
    for (ll i = 1; i <= n; i++) {
        ll l = qh, r = qt, m, id1, id2;
        while (l < r) {
            m = l + r >> 1;
            if (y(q[m]) - x(q[m]) * k(i) <= y(q[m + 1]) - x(q[m + 1]) * k(i))r = m;
            else l = m + 1;
        }
        l = q[l];
        f[i] = f[l] + s * (c[n] - c[l]) + t[i] * (c[i] - c[l]);
        while (qt > qh && (x(q[qt]) - x(q[qt - 1])) * (y(i) - y(q[qt])) <= (y(q[qt]) - y(q[qt - 1])) * (x(i) - x(q[qt])))qt--;
        q[++qt] = i;
    }
    printf("%lld", f[n]);
    return 0;
}
