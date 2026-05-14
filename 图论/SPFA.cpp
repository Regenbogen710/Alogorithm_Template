#pragma GCC optmize(2)
#pragma GCC optmize("inline")
#pragma GCC optmize("Ofast,fast-math")
#include<bits/stdc++.h>
#define ll long long
#define reg register
//#define putchar putchar_unlocked
//static char *p1,*p2,buf[1<<21];
//#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;

inline bool read(ll &x) {
    x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    if (f)x = -x;
}

inline void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)write(x / 10);
    putchar(x % 10 ^ 48);
}

const ll INF = 0x3effffff;
const ll N = 1010;
const ll M = 20010;


ll k;
ll n, m, w;
ll u, v, z;

struct mp {
    ll head[N], cnt;
    ll nxt[M], to[M], w[M];
    ll dis[N];

    inline void add(ll u,ll v,ll weight) {
        cnt++;
        to[cnt] = v;
        w[cnt] = weight;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    inline bool spfa(ll s,ll t,ll xx) {
        queue<ll> q;
        bitset<N> inq;
        memset(dis, 0x3f, sizeof(dis));
        dis[s] = 0;
        inq[s] = 1;
        q.push(s);
        while (!q.empty()) {
            ll x = q.front();
            q.pop();
            inq[x] = 0;
            for (ll i = head[x]; i; i = nxt[i]) {
                ll sum = dis[x];
                if (w[i] > xx)sum++;
                if (sum < dis[to[i]]) {
                    dis[to[i]] = sum;
                    if (!inq[to[i]]) {
                        q.push(to[i]);
                        inq[to[i]] = 1;
                    }
                }
            }
        } //
        //		printf("dis:%lld\n",dis[t]);
        return dis[t] <= k;
    }
} g;


int main() {
    read(n);
    read(m);
    read(k);
    for (ll i = 1; i <= m; i++) {
        read(u);
        read(v);
        read(w);
        g.add(u, v, w);
        g.add(v, u, w);
    }
    ll r = 1000001, l = 0, mid;
    while (l < r) {
        mid = l + r >> 1;
        if (g.spfa(1, n, mid))r = mid;
        else l = mid + 1;
    }
    if (l > 1000000) {
        write(-1);
        return 0;
    }
    write(l);
    return 0;
}
