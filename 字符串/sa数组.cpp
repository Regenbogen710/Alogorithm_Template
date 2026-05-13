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
const ll N = 1e6 + 10, M = 360 + 10, mod = 998244353;
ll n, k, m, x, y, q;
bool Mbe;

namespace SA{
    ll buc[N], rk[N], ork[N], id[N];
    void clac_sa(const char *s, ll *sa) {
        ll n = strlen(s + 1), p = 0, m = 1 << 7;

        memset(buc, 0, sizeof(buc[0]) * (max(n + 10, 256ll)));
        memset(ork, 0, sizeof(ork[0]) * (n + 10));
        memset(rk, 0, sizeof(rk[0]) * (n + 10));
        memset(id, 0, sizeof(id[0]) * (n + 10));

        rep(i, 1, n) buc[rk[i] = s[i]]++;
        rep(i, 1, m) buc[i] += buc[i - 1];
        rep(i, 1, n) sa[buc[rk[i]]--] = i;
        for (ll w = 1;;m = p, p = 0, w <<= 1) {
            rep(i, n - w + 1, n) id[++p] = i;
            rep(i, 1, n) if (sa[i] > w) id[++p] = sa[i] - w;
            memset(buc, 0, sizeof(ll) * (m + 1));
            memcpy(ork, rk, sizeof(ll) * (n + 1));
            p = 0;
            rep(i, 1, n) buc[rk[i]]++;
            rep(i, 1, m) buc[i] += buc[i - 1];
            per(i, n, 1) sa[buc[rk[id[i]]]--] = id[i];
            rep(i, 1, n) rk[sa[i]] = (ork[sa[i - 1]] == ork[sa[i]] && ork[sa[i - 1] + w] == ork[sa[i] + w]) ? p : ++p;
            if (p == n) break;
        }
    }
    void calc_ht(char *s, ll *sa, ll *ht, ll n) {
        for(ll i = 1, k = 0; i <= n; i++) {
            if(k) k--;
            while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
            ht[rk[i]] = k;
        }
    }
}

using namespace SA;
char s[N];


ll sa[N], ht[N];

ll st[20][N];

inline ll Lcp (ll l, ll r){
    if(l > r) swap(l, r);
    ll k = __lg(r - l + 1);
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

bool Med;
inline void solve(){


    scanf("%s %lld", s + 1, &q);

    SA::clac_sa(s, sa);
    n = strlen(s + 1);

    rep(i, 1, n) st[0][i] = ht[i];
    rep(k, 1, __lg(n)){
        for(ll i = 1; i  + (1 << k) - 1 <= n; i++){
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }


    putchar('\n');

    memset(sa, 0, sizeof(sa[0]) * (n + 10));
    memset(ht, 0, sizeof(ht[0]) * (n + 10));
    // rep(i, 0, 19) rep(j, 0, n + 5) st[i][j] = 0;
    // del(now);
}



int main() {
    ll clk = clock();
    // ios::sync_with_stdio(0);
    // cin.tie(0), cout.tie(0);
    ll q = 1;
#ifdef MULTI
    cin >> q;
#endif
    while (q--) {
        // cout << q << endl;
        solve();
    }

    // cerr << ((&Mbe - &Med) / 1024.0 / 1024.0) << " Mb" << endl;
    // cerr << ((clock() - clk) * 1.0 / CLOCKS_PER_SEC ) << " S" << endl;
    return 0;
}