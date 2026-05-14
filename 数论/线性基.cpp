#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n;
struct xorbase {
    vector<ll> p;

    xorbase(ll n){p.resize(n);}

    void insert(ll x) {
        assert(!p.empty());
        for (ll i = (ll)p.size() - 1; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            if (!p[i]) return p[i] = x, void();
            x ^= p[i];
        }
    }

    ll querymax() {
        assert(!p.empty());
        ll res = 0;
        for (ll i = (ll)p.size() - 1; i >= 0; i--) res = max(res, res ^ p[i]);
        return res;
    }
};

int main() {
    ll n = 0;
    cin >> n;
    xorbase base(55);
    for (ll i = 1; i <= n; i++) {
        ll x = 0;
        cin >> x;
        base.insert(x);
    }

    cout << base.querymax() << endl;

    return 0;
}