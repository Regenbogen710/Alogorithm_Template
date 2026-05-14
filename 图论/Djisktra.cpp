#include<bits/stdc++.h>
#define ll long long
#define reg register
//#define putchar putchar_unlocked
//static char *p1,&p2,buf[1<<21];
//#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;

inline void read(ll &x) {
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

const ll INF = 0x3fffffff;
const ll N = 2510;
const ll M = 6210;


struct mp {
    ll nxt, to, w;
} g[M << 1];

ll head[N], cnt = 1;

inline void add(ll u,ll v,ll w) {
    g[cnt].to = v;
    g[cnt].w = w;
    g[cnt].nxt = head[u];
    head[u] = cnt;
    cnt++;
}

ll n, m, s, t;
ll u, v, w;
ll ans;


bitset<N> vis;
ll dis[N];


struct node {
    ll num, id;
    bool operator <(const node &cmp) const {return num > cmp.num;}
};
priority_queue<node>q;


inline ll dijsktra(ll s,ll t) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    vis[s] = 1;
    node x;
    x.num = dis[s];
    x.id = s;
    q.push(x);
    while (!q.empty()) {
        node x = q.top();
        q.pop();
        for (ll i = head[x.id]; i; i = g[i].nxt) {
            if (!vis[g[i].to] && dis[g[i].to] > dis[x.id] + g[i].w) {
                dis[g[i].to] = dis[x.id] + g[i].w;
                node dat;
                dat.id = g[i].to;
                dat.num = dis[x.id] + g[i].w;
                q.push(dat);
            }
        }
    }
    return dis[t];
}

int main() {
    read(n);
    read(m);
    read(s);
    read(t);
    for (ll i = 1; i <= m; i++) {
        read(u);
        read(v);
        read(w);
        add(u, v, w);
        add(v, u, w);
    }
    write(dijsktra(s, t));
    return 0;
}
