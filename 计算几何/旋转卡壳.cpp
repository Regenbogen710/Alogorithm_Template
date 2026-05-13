// #pragma GCC optimize(2)
#include<bits/stdc++.h>
// #define max(a,b) (a<b)?b:a
typedef long long ll;
using namespace std;
const ll N = 1e6 + 10;

struct point2 {
    ll x, y;
    bool operator <(const point2 &a) const { return (x != a.x) ? x < a.x : y < a.y; }
} p[N], hull[N];

ll n, m;

inline ll cross(point2 p0, point2 p1, point2 p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

inline ll dis(point2 a, point2 b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

inline void andrew() {
    for (ll i = 1; i <= n; i++) {
        while (m > 1 && cross(hull[m - 2], hull[m - 1], p[i]) <= 0)m--;
        hull[m++] = p[i];
    }
    ll k = m;
    for (ll i = n - 1; i >= 1; i--) {
        while (m > k && cross(hull[m - 2], hull[m - 1], p[i]) <= 0)m--;
        hull[m++] = p[i];
    }
    if (n > 1)m--;
}

inline ll D() {
    ll ans = 0;
    for (ll i = 0, j = 1; i < m; i++) {
        while (cross(hull[i], hull[i + 1], hull[j]) < cross(hull[i], hull[i + 1], hull[j + 1]))j = (j + 1) % m;
        ans = max(ans, max(dis(hull[i], hull[j]), dis(hull[i + 1], hull[j])));
    }
    return ans;
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)scanf("%lld %lld", &p[i].x, &p[i].y);
    sort(p + 1, p + 1 + n);
    andrew();
    printf("%lld", D());
}
