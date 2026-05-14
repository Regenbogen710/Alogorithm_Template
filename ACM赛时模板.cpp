#include<bits/stdc++.h>
using namespace std;

// #include<bits/extc++.h>
// using namespace __gnu_cxx;


#define rep(i, l, r) for(ll i = (l); i <= (r); i++)
#define per(i, r, l) for(ll i = (r); i >= (l); i--)

#define all(a) a.begin(), a.end()
#define all1(a) a.begin() + 1, a.end()

typedef long long ll;
typedef long long i64;
typedef pair<ll, ll> pll;


template<typename T, typename Z>
inline void chkmax(T &x, const Z &y) { x = x > y ? x : y; }

template<typename T, typename Z>
inline void chkmin(T &x, const Z &y) { x = x < y ? x : y; }



bool Mbe;
const ll N = 2e6 + 10, M = 360 + 10, mod = 998'244'353;
ll n, k, m, x, y, q, h, p;

void init() {

}


// #define DEBUG
#define SYNC
// #define MULTI

inline void solve() {

}

bool Med;


int main() {
#ifdef SYNC
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    ll q = 1, clk1 = clock();

#ifdef MULTI
    cin >> q;
#endif
    init();
    while (q--) {
        solve();
    }
#ifdef DEBUG
    cerr << ((&Med - &Mbe) / 1024.0 / 1024.0) << " Mb" << endl;
    cerr << ((clock() - clk1) * 1000.0 / CLOCKS_PER_SEC ) << " Ms" << endl;
#endif
    return 0;
}