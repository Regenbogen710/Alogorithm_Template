//  Luogu P6216

#include<bits/stdc++.h>

#define cbug(x) cerr<<"[ "<<(#x)<<" ]:"<<x<<" "<<"\n"
#define rep(i, l, r) for(ll i=(l);i<=(r);i++)
#define pre(i, r, l) for(ll i=(r);i>=(l);i--)
using namespace std;
typedef int ll;

bool Memory_begin;

//#define bogen
#ifdef bogen
const ll LEN = 1 << 22;
char buf[LEN], *P1, *P2;
#define getchar() (P1 == P2 && (P2 = (P1 = buf) + fread(buf, 1, LEN, stdin), P1 == P2)? EOF: *P1++)
#endif

inline void File(string file, string sec = "") {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((((sec == "") ? file : sec) + ".out").c_str(), "w", stdout);
}

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

template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { x = x > y ? x : y; }

template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { x = x < y ? x : y; }

const ll N = 1.1e7 + 10, M = 1e5 + 10, mod = 998244353;
ll n, m, ans;
ll z[N << 1];
char s[N << 1];
bool Memory_end;

int main() {

    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (ll i = n; i > 0; i--) {
        s[i * 2] = s[i];
        s[i * 2 - 1] = '#';
    }
    s[0] = '@', s[2 * n + 1] = '#', s[2 * n + 2] = '!';
    for (ll c = 0, r = 0, i = 1; i < n * 2; i++) {
        z[i] = (i > r)? 1 : min(z[2 * c - i], r - i + 1);
        while (s[i - z[i]] == s[i + z[i]])z[i]++;
        chkmax(ans, z[i] - 1);
        if (i + z[i] - 1 > r)c = i, r = i + z[i] - 1;
    }
    cout << ans ;
    // fprintf(stderr, "\n%.3lf Ms\n", (((double) (clock()) / CLOCKS_PER_SEC)));
    // fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    // if ((&Memory_end - &Memory_begin) / 1048576.0 > 128)return fprintf(stderr, "MLE"), 0;
    return 0;
}

/*
Start coding at 22:00
Finish debugging at ???
*/