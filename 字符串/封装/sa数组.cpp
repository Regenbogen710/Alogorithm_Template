#include<bits/stdc++.h>

#define rep(i, l, r) for(ll i = (l); i <= (r); i++)
#define per(i, r, l) for(ll i = (r); i >= (l); i--)

using namespace std;
typedef long long ll;
typedef long long i64;

template <typename T, typename Z>
inline void chkmax(T& x, const Z& y) { x = x > y ? x : y; }

template <typename T, typename Z>
inline void chkmin(T& x, const Z& y) { x = x < y ? x : y; }


#define MULTI
const ll N = 1e6 + 10, mod = 998244353;
ll k, m, x, y, q;          // 移除原先的全局 n，避免与结构体成员混淆
bool Mbe;

struct SA {
    ll n;
    vector<ll> sa, rk, ht;
    vector<vector<ll>> st;
    // 临时数组
    vector<ll> buc, ork, id;

    // 仅构建后缀数组（sa 和 rk）
    void build(char *s) {
        n = strlen(s + 1);
        clac_sa(s);
    }

    // 构建高度数组 ht
    void build_ht(char *s) {
        ht.resize(n + 2);
        calc_ht(s);
    }

    // 构建 ST 表（用于 LCP 查询）
    void build_st() {
        ll maxk = __lg(n) + 1;
        st.assign(maxk, vector<ll>(n + 2, 0));
        rep(i, 1, n) st[0][i] = ht[i];
        rep(k, 1, maxk - 1) {
            for (ll i = 1; i + (1ll << k) - 1 <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1ll << (k - 1))]);
            }
        }
    }

    // 查询排名为 l 和 r 的后缀的 LCP
    inline ll lcp(ll l, ll r) {
        if (l > r) swap(l, r);
        ll k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1ll << k) + 1]);
    }

    // 清空所有数组
    void clear() {
        n = 0;
        sa.clear(); rk.clear(); ht.clear();
        st.clear();
        buc.clear(); ork.clear(); id.clear();
    }

private:
    void clac_sa(char *s) {
        ll m = 1 << 7, p = 0;
        sa.resize(n + 2, 0); rk.resize(n + 2, 0);
        ork.resize(n + 2, 0); id.resize(n + 2, 0);
        buc.assign(max(n + 10, 256ll) + 10, 0);   // 足够大的计数数组

        rep(i, 1, n) buc[rk[i] = s[i]]++;
        rep(i, 1, m) buc[i] += buc[i - 1];
        rep(i, 1, n) sa[buc[rk[i]]--] = i;
        for (ll w = 1;; m = p, p = 0, w <<= 1) {
            if ((ll)buc.size() < m + 10) buc.resize(m + 10, 0);
            rep(i, n - w + 1, n) id[++p] = i;
            rep(i, 1, n) if (sa[i] > w) id[++p] = sa[i] - w;
            fill(buc.begin(), buc.begin() + m + 1, 0);
            copy(rk.begin(), rk.begin() + n + 1, ork.begin());
            p = 0;
            rep(i, 1, n) buc[rk[i]]++;
            rep(i, 1, m) buc[i] += buc[i - 1];
            per(i, n, 1) sa[buc[rk[id[i]]]--] = id[i];
            rep(i, 1, n) rk[sa[i]] = (ork[sa[i - 1]] == ork[sa[i]] && ork[sa[i - 1] + w] == ork[sa[i] + w]) ? p : ++p;
            if (p == n) break;
        }
    }

    void calc_ht(char *s) {
        for (ll i = 1, k = 0; i <= n; i++) {
            if (k) k--;
            while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
            ht[rk[i]] = k;
        }
    }
};

char s[N];
SA sa_solver;   // SA 结构体实例

bool Med;
inline void solve() {
    scanf("%s %lld", s + 1, &q);

    sa_solver.build(s);
    sa_solver.build_ht(s);
    sa_solver.build_st();

    putchar('\n');
    sa_solver.clear();
}

int main() {
    ll clk = clock();
    ll t = 1;
#ifdef MULTI
    cin >> t;
#endif
    while (t--) {
        solve();
    }
    return 0;
}