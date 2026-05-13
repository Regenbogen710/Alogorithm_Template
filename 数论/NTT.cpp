#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
typedef long long ll;

ll Memory_begin;
const ll N = 4e6 + 10;
const ll mod = 998244353, G = 3;

struct NTT {
    ll limit, l;
    ll rev[N];

    ll qpow(ll x, ll k) {
        ll res = 1;
        while (k) {
            if (k & 1) res = res * x % mod;
            x = x * x % mod;
            k >>= 1;
        }
        return res;
    }

    void init(int len) {
        limit = 1, l = 0;
        while (limit <= len) limit <<= 1, l++;
        for (int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }

    void ntt(ll *f, int opt) {
        for (int i = 0; i < limit; i++) if (i < rev[i]) swap(f[i], f[rev[i]]);
        for (int mid = 1; mid < limit; mid <<= 1) {
            ll Wn = qpow(G, (mod - 1) / (mid << 1));
            if (opt == -1) Wn = qpow(Wn, mod - 2);
            for (int r = mid << 1, i = 0; i < limit; i += r) {
                ll w = 1;
                for (int j = 0; j < mid; j++, w = w * Wn % mod) {
                    ll x = f[i + j], y = w * f[i + j + mid] % mod;
                    f[i + j] = (x + y) % mod;
                    f[i + j + mid] = (x - y + mod) % mod;
                }
            }
        }
        if (opt == -1) {
            ll inv = qpow(limit, mod - 2);
            for (ll i = 0; i < limit; i++) f[i] = f[i] * inv % mod;
        }
    }

    void calc(ll *a, ll *b) {
        ntt(a, 1), ntt(b, 1);
        for (int i = 0; i < limit; i++) a[i] = a[i] * b[i] % mod;
        ntt(a, -1);
    }

} ntt;

ll clock_begin, Memory_end;
ll n, m, a[N], b[N];
char s[N], t[N];
int main() {
    clock_begin = clock();
    cin >> m >> n;

    ntt.init(n + m);


    reverse(a, a + m);
    ntt.calc(a, b);


    //    fprintf(stderr, "%.3lf MB\n", -(&Memory_begin - &Memory_end) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start at下午8:00
//End at