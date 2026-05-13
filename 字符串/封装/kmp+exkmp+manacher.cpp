#include<bits/stdc++.h>

#define rep(i, l, r) for(ll i=(l);i<=(r);i++)
#define pre(i, r, l) for(ll i=(r);i>=(l);i--)
using namespace std;
typedef long long ll;

// ---------- 快速读模板 (保留) ----------
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
inline void read(T &x, Args &... args) { read(x); read(args...); }

template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { x = x > y ? x : y; }
template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { x = x < y ? x : y; }

// ============= ExKMP 结构体 =============
struct ExKMP {
    vector<ll> z, lcp;
    void build_z(char *t) {
        ll m = strlen(t + 1);
        z.assign(m + 2, 0);
        z[1] = m;
        for (ll i = 2, l = 0, r = 0; i <= m; i++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
            while (i + z[i] <= m && t[z[i] + 1] == t[z[i] + i]) z[i]++;
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
    }
    void build_lcp(char *s, char *t) {
        ll n = strlen(s + 1), m = strlen(t + 1);
        lcp.assign(n + 2, 0);
        for (ll i = 1, l = 0, r = 0; i <= n; i++) {
            if (i <= r) lcp[i] = min(z[i - l + 1], r - i + 1);
            while (i + lcp[i] <= n && s[i + lcp[i]] == t[lcp[i] + 1]) lcp[i]++;
            if (i + lcp[i] - 1 > r) l = i, r = i + lcp[i] - 1;
        }
    }
    void clear() { z.clear(); lcp.clear(); }
};

// ============= KMP 结构体 =============
struct KMP {
    vector<ll> nxt;
    void build_nxt(char *s) {
        ll n = strlen(s + 1);
        nxt.assign(n + 2, 0);
        for (ll i = 2, j = 0; i <= n; i++) {
            while (j && s[j + 1] != s[i]) j = nxt[j];
            if (s[j + 1] == s[i]) j++;
            nxt[i] = j;
        }
    }
    void match(char *txt, char *pat, vector<ll> &pos) {
        ll m = strlen(txt + 1), n = strlen(pat + 1);
        pos.clear();
        for (ll i = 1, j = 0; i <= m; i++) {
            while (j && pat[j + 1] != txt[i]) j = nxt[j];
            if (pat[j + 1] == txt[i]) j++;
            if (j == n) { pos.push_back(i - n + 1); }
        }
    }
    void clear() { nxt.clear(); }
};

// ============= Manacher 结构体 =============
struct Manacher {
    vector<ll> z;   // 回文半径数组
    string s;       // 处理后的字符串（包含分隔符）
    void init(char *str) {
        ll n = strlen(str + 1);
        s.assign(2 * n + 10, 0);
        s[0] = '@';
        for (ll i = n; i > 0; i--) {
            s[i * 2] = str[i];
            s[i * 2 - 1] = '#';
        }
        s[2 * n + 1] = '#';
        s[2 * n + 2] = '!';
    }
    ll solve() {
        ll len = s.size() - 2;   // 有效部分长度
        z.assign(len + 2, 0);
        ll ans = 0;
        for (ll c = 0, r = 0, i = 1; i <= len; i++) {
            z[i] = (i > r) ? 1 : min(z[2 * c - i], r - i + 1);
            while (s[i - z[i]] == s[i + z[i]]) z[i]++;
            chkmax(ans, z[i] - 1);
            if (i + z[i] - 1 > r) c = i, r = i + z[i] - 1;
        }
        return ans;
    }
    void clear() { z.clear(); s.clear(); }
};

// ============= 以下为演示 main =============
char str1[20000010], str2[20000010]; // 缓冲区

int main() {
    // ----- 演示 manacher 的使用（与原 manacher.cpp 功能一致）-----
    scanf("%s", str1 + 1);
    Manacher man;
    man.init(str1);
    cout << man.solve() << endl;
    man.clear();

    /*
    // ----- 演示 ExKMP 的使用 -----
    scanf("%s %s", str1 + 1, str2 + 1);
    ExKMP ex;
    ex.build_z(str2);               // str2 为模式串 t
    ex.build_lcp(str1, str2);       // str1 文本，str2 模式
    ll ans1 = 0, ans2 = 0;
    ll m = strlen(str2 + 1), n = strlen(str1 + 1);
    for(ll i = 1; i <= m; i++) ans1 ^= (i * ex.z[i] + i);
    for(ll i = 1; i <= n; i++) ans2 ^= (i * ex.lcp[i] + i);
    printf("%lld\n%lld\n", ans1, ans2);
    ex.clear();

    // ----- 演示 KMP 的使用 -----
    scanf("%s %s", str2 + 1, str1 + 1);  // 先模式串后文本串
    KMP kmp;
    kmp.build_nxt(str1);
    vector<ll> pos;
    kmp.match(str2, str1, pos);   // str2 文本, str1 模式
    for(ll p : pos) printf("%lld\n", p);
    for(ll i = 1; i <= strlen(str1+1); i++) printf("%lld ", kmp.nxt[i]);
    putchar('\n');
    kmp.clear();
    */

    return 0;
}