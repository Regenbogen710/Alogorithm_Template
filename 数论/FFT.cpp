// Created by regenbogen on 九月-01   and is--星期五
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
typedef long long ll;

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

ll Memory_begin;
const ll N = 4e6 + 10;
const double pi = acos(-1);
ll n, m, c[N], limit = 1, l = 0;

struct Complex {
    double real, imag;

    Complex() {}

    template<typename T, typename Z>
    inline Complex(T REAL, Z IMAG) { real = REAL, imag = IMAG; }

    inline Complex operator+(Complex A) { return Complex(real + A.real, imag + A.imag); }
    inline Complex operator-(Complex A) { return Complex(real - A.real, imag - A.imag); }
    inline Complex operator/(double k) { return Complex(real / k, imag / k); }

    inline Complex operator*(Complex A) {
        return Complex(real * A.real - imag * A.imag, imag * A.real + real * A.imag);
    }
} a[N];

inline void NTT(ll limit, ll opt) {
    Complex W(cos(pi), opt * sin(pi)), w(1, 0);
    for (int i = 0; i < limit; i++)if (i < c[i])swap(a[i], a[c[i]]);
    for (int mid = 1; mid < limit; mid <<= 1, W = Complex(cos(pi / mid), opt * sin(pi / mid))) {
        for (int r = mid << 1, i = 0; i < limit; i += r, w = Complex(1, 0)) {
            for (int j = 0; j < mid; j++, w = w * W) {
                Complex x = a[i + j], y = w * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
    if (opt == -1)for (ll i = 0; i < limit; i++)a[i] = a[i] / limit;
}

ll clock_begin, Memory_end;

int main() {
    clock_begin = clock();
    read(n, m);
    for (int i = 0; i <= n; i++)read(a[i].real);
    for (int i = 0; i <= m; i++)read(a[i].imag);
    while (limit <= n + m)limit <<= 1, l++;
    for (int i = 0; i < limit; i++)c[i] = (c[i >> 1] >> 1) | ((i & 1) << (l - 1));
    NTT(limit, 1);
    for (int i = 0; i < limit; i++)a[i] = a[i] * a[i];
    NTT(limit, -1);
    for (int i = 0; i <= n + m; i++)printf("%lld ", (ll) (a[i].imag / 2 + 0.5));
    //    fprintf(stderr, "%.3lf MB\n", -(&Memory_begin - &Memory_end) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start at下午8:00
//End at
