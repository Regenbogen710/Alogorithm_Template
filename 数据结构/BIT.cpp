#include<bits/stdc++.h>
using namespace std;


/** region Templates */
namespace Mine {
    typedef long long ll;
    typedef long long i64;

    template <typename T>
    class BIT {
    private:
        int n;
        T *a, val;
        function<T(T, T)> op;
    public:
        BIT(int size, function<T(T, T)> option ,const T &val): n(size), val(val), op(option) {
            a = new T[n];
            for (int i = 0 ; i < n ; i++) a[i] = val;
        }

        void add(int p, const T &v) {
            if (p == 0) a[0] = op(a[0], v);
            else for (int i = p ; i < n && i; i += (i & -i)) a[i] = op(a[i], v);
        }

        T ask(ll p) {
            T ans = a[0];
            for (int i = p ; i; i -= (i & -i)) ans = op(ans, a[i]);
            return ans;
        }
    };


}
/** endregion */

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