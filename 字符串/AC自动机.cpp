//  Luogu P5357

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

const ll N = 2e5 + 10, M = 2e6 + 10, mod = 998244353;
ll n, m;

namespace AC {
    ll root, node_cnt;

    struct node {
        ll son[26], fail, ru, ans, bl;
        inline ll &operator[](ll x) { return son[x]; }
    } tr[N];

    ll Map[N], bl_cnt;

    inline ll newnode() { return ++node_cnt; }
    inline ll newbl() { return ++bl_cnt; }
    inline void init() { node_cnt = 0, root = newnode(); }

    inline void ins(const char *s, const ll id) {
        ll len = strlen(s + 1);
        ll x = root;
        for (ll i = 1; i <= len; i++) {
            ll son = s[i] - 'a';
            if (tr[x][son] == 0)tr[x][son] = newnode();
            x = tr[x][son];
        }
        if (tr[x].bl == 0) tr[x].bl = newbl();
        Map[id] = tr[x].bl;
    }

    inline void build_Fail() {
        queue<ll> q;
        for (ll i = 0; i < 26; i++) tr[0][i] = root;
        q.emplace(root);
        while (!q.empty()) {
            ll x = q.front();
            q.pop();
            for (ll i = 0; i < 26; i++) {
                ll &to = tr[x][i], fail = tr[x].fail;
                if (to) {
                    tr[to].fail = tr[fail][i];
                    tr[tr[fail][i]].ru++;
                    q.emplace(to);
                } else to = tr[fail][i];
            }
        }
    }

    inline void query(const char *s) {
        ll len = strlen(s + 1);
        ll x = root;
        for (ll i = 1; i <= len; i++) {
            x = tr[x][s[i] - 'a'];
            tr[x].ans++;
        }
    }

    ll ans[N];

    inline void topu() {
        queue<ll> q;
        for (ll i = 1; i <= node_cnt; i++) if (tr[i].ru == 0) q.emplace(i);
        while (!q.empty()) {
            ll x = q.front(), fail = tr[x].fail;
            q.pop();
            ans[tr[x].bl] = tr[x].ans;
            tr[fail].ans += tr[x].ans;
            if (--tr[fail].ru == 0) q.emplace(fail);
        }
    }

    inline void Answer() {
        for (ll i = 1; i <= n; i++) {
            printf("%d\n", ans[Map[i]]);
        }
    }
}

char s[M];
bool Memory_end;

int main() {
    AC::init();
    read(n);
    rep(i, 1, n) {
        scanf("%s", s + 1);
        AC::ins(s, i);
    }
    AC::build_Fail();
    scanf("%s", s + 1);
    AC::query(s);
    AC::topu();
    AC::Answer();
    return 0;
}

/*
Start coding at 11:29
Finish debugging at ???
*/
