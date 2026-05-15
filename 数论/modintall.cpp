#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct modint {
    static ll MOD;
    ll x;

    modint(ll x = 0) : x((x % MOD + MOD) % MOD) {}

    static inline void change_mod(ll new_mod) { MOD = new_mod; }
    
    // modint 之间的四则运算
    inline modint operator+(const modint &b) const { return modint(x + b.x >= MOD ? x + b.x - MOD : x + b.x); }
    inline modint operator-(const modint &b) const { return modint(x - b.x < 0 ? x - b.x + MOD : x - b.x); }
    inline modint operator*(const modint &b) const { return modint(x * b.x % MOD); }
    inline modint operator/(const modint &b) const { return *this * b.inv(); }

    inline modint &operator+=(const modint &b) { x = x + b.x >= MOD ? x + b.x - MOD : x + b.x; return *this; }
    inline modint &operator-=(const modint &b) { x = x - b.x < 0 ? x - b.x + MOD : x - b.x; return *this; }
    inline modint &operator*=(const modint &b) { x = x * b.x % MOD; return *this; }
    inline modint &operator/=(const modint &b) { return *this = *this * b.inv(); }

    // 混合运算：modint 与 整数 (ll)
    inline modint operator+(ll b) const { return *this + modint(b); }
    inline modint operator-(ll b) const { return *this - modint(b); }
    inline modint operator*(ll b) const { return *this * modint(b); }
    inline modint operator/(ll b) const { return *this / modint(b); }

    friend inline modint operator+(ll a, const modint &b) { return modint(a) + b; }
    friend inline modint operator-(ll a, const modint &b) { return modint(a) - b; }
    friend inline modint operator*(ll a, const modint &b) { return modint(a) * b; }
    friend inline modint operator/(ll a, const modint &b) { return modint(a) / b; }

    inline modint &operator+=(ll b) { return *this += modint(b); }
    inline modint &operator-=(ll b) { return *this -= modint(b); }
    inline modint &operator*=(ll b) { return *this *= modint(b); }
    inline modint &operator/=(ll b) { return *this /= modint(b); }

    inline modint pow(ll k) const {
        modint res = 1, a = *this;
        while (k) {
            if (k & 1) res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }

    inline modint inv() const { return pow(MOD - 2); }   // 要求 MOD 为质数
    inline bool operator==(const modint &b) const { return x == b.x; }
    inline bool operator!=(const modint &b) const { return x != b.x; }
};

ll modint::MOD = 998244353;