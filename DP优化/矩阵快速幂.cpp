#include<bits/stdc++.h>
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

const ll T = 2, mod = 1e9 + 7;

struct martix {
    ll a[T][T];
    inline void init() { memset(a, 0, sizeof(a)); }
    inline ll *operator[](const ll &x) { return a[x]; }

    inline martix operator*(martix b) const {
        martix ans;
        ans.init();
        for (ll i = 0; i < T; i++)
            for (ll j = 0; j < T; j++)
                for (ll k = 0; k < T; k++)
                    ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % mod;
        return ans;
    }
} a, base;

ll n, k;

inline martix martix_fpow(martix A, ll temp) {
    ll t = temp;
    martix base = A, ans;
    ans.init();
    for (ll i = 0; i < T; i++)ans[i][i] = 1;
    while (t) {
        if (t & 1)ans = ans * base;
        base = base * base;
        t >>= 1;
    }
    return ans;
}

int main() {
    a.init();
    base.init();
    base[0][0] = 1;
    base[0][1] = 1;
    base[1][0] = 1;
    a[0][0] = 1;
    a = a * martix_fpow(base, read() - 1);
    printf("%lld ", a[0][0]);
    return 0;
}
