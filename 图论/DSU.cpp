#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')f |= ch == '-', ch = getchar();
    while (ch >= '0' && ch <= '9')x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}

inline void read(ll &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

struct unionfind {
    ll n, *fa;

    unionfind(ll n) : n(n) {
        fa = new ll[n];
        for (ll i = 0; i < n; i++)fa[i] = i;
    }

    ll find(ll son) { return (fa[son] == son) ? son : find(fa[son]); }
    inline void setup(ll u, ll v) { fa[find(u)] = find(v); }
    inline bool query(ll u, ll v) { return find(u) == find(v); }
};

int main() {
    return 0;
}
