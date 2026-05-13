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

const ll N = 2e7 + 10;


inline void exkmp(char *s, ll *z) {
    ll m = strlen(s + 1);
    z[1] = m;
    for (ll i = 2, l = 0, r = 0; i <= m; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
        while (i + z[i] <= m && s[z[i] + 1] == s[z[i] + i])z[i]++;
        if (i + z[i] - 1 > r)l = i, r = i + z[i] - 1;
    }
}

inline void excmp(char *s, char *t, ll *lcp, ll *z) {
    ll n = strlen(s + 1);
    for (ll i = 1, l = 0, r = 0; i <= n; i++) {
        if (i <= r)lcp[i] = min(z[i - l + 1], r - i + 1);
        while (i + lcp[i] <= n && s[i + lcp[i]] == t[lcp[i] + 1])lcp[i]++;
        if (i + lcp[i] - 1 > r)l = i, r = i + lcp[i] - 1;
    }
}

ll z[N], lcp[N], n, m, ans1, ans2;
char s[N], t[N];

int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    exkmp(t, z);
    excmp(s, t, lcp, z);
    //t与s的每个后缀的lcp
    for (ll i = 1; i <= m; i++)ans1 ^= (i * z[i] + i);
    for (ll i = 1; i <= n; i++)ans2 ^= (i * lcp[i] + i);
    printf("%lld \n%lld\n", ans1, ans2);
    return 0;
}
