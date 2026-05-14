#include<bits/stdc++.h>
using namespace std;

namespace Mine {

#define rep(i, l, r) for(ll i = (l); i <= (r); i++)
#define per(i, r, l) for(ll i = (r); i >= (l); i--)

#define all(a) a.begin(), a.end()
#define all1(a) a.begin() + 1, a.end()

    typedef long long ll;
    typedef long long i64;
    random_device rd_Seed;
    mt19937_64 RND(rd_Seed());
    inline ll rnd(ll l, ll r) {
        return (RND() >> 1) % (r - l + 1) + l;
    }

}
using namespace Mine;

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
    cerr << ((&Mbe - &Med) / 1024.0 / 1024.0) << " Mb" << endl;
    cerr << ((clock() - clk1) * 1000.0 / CLOCKS_PER_SEC ) << " Ms" << endl;
#endif
    return 0;
}
//为什么这里总是乱报错