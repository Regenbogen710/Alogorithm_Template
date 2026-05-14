//Created by regenbogen on 23-8-19.
#include<bits/stdc++.h>
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

const ll N = 1e5 + 10;

struct node {
    ll x, y;

    node() {
    }

    node(ll x_, ll y_) { x = x_, y = y_; }
    inline bool operator <(const node &B) const { return (x < B.x) || (x == B.x && y < B.y); }
    inline node operator +(const node &B) const { return node(x + B.x, y + B.y); }
    inline node operator -(const node &B) const { return node(x - B.x, y - B.y); }
    inline node operator *(const ll &k) const { return node(x * k, y * k); }
    inline ll operator &(const node &B) const { return x * B.y - y * B.x; }
    inline ll operator *(const node &B) const { return x * B.x + y * B.y; }
    inline ll len() { return x * x + y * y; }
    inline void write() { printf("(%lld,%lld)\n", x, y); }
};

typedef node Vector;
typedef node Point;

inline void read(node &A) {
    return read(A.x, A.y);
}

inline void convexhull(Point *point, Point *hull, ll &cnt, ll n) {
    sort(point + 1, point + n + 1);
    for (ll i = 1; i <= n; i++) {
        while (((hull[cnt] - hull[cnt - 1]) & (point[i] - hull[cnt])) <= 0 && cnt > 1)cnt--;
        hull[++cnt] = point[i];
    }
    ll k = cnt;
    for (ll i = n - 1; i > 0; i--) {
        while (((hull[cnt] - hull[cnt - 1]) & (point[i] - hull[cnt])) <= 0 && cnt > k)cnt--;
        hull[++cnt] = point[i];
    }
    //    for(ll i=1;i<=cnt;i++)hull[i].write();
    //    cout<<"#########\n";
}

struct Hull {
    node point[N], hull[N];
    ll cnt;
    inline node operator [](const ll &x) const { return hull[x]; }

    inline void creat(ll n, ll opt) {
        for (ll i = 1; i <= n; i++)read(point[i]);
        for (ll i = 1; i <= n; i++)point[i] = point[i] * opt;
        convexhull(point, hull, cnt, n);
    }
} A, B;

Vector C[N], Q, v1[N], v2[N], st, T[N];
ll k, tot;

inline void minkowski() {
    st = C[k = 1] = B[1] + A[1];
    ll n1 = A.cnt, n2 = B.cnt, i = 1, j = 1;
    for (ll i = 1; i < n1; i++)v1[i] = A[i + 1] - A[i];
    for (ll i = 1; i < n2; i++)v2[i] = B[i + 1] - B[i];
    while (i < n1 && j < n2) {
        if ((v1[i] & v2[j]) > 0)C[k + 1] = C[k] + v1[i++], k++;
        else C[k + 1] = C[k] + v2[j++], k++;
    }
    while (i < n1)C[k + 1] = C[k] + A[i + 1] - A[i], k++, i++;
    while (j < n2)C[k + 1] = C[k] + B[j + 1] - B[j], k++, j++;
}

inline bool cmp(Vector A, Vector B) {
    return ((A & B) > 0) || ((A & B) == 0 && (A.len() < B.len()));
}

inline bool hullcheck(node q) {
    if ((q & T[1]) > 0 || (T[tot] & q) > 0)return 0;
    ll l = lower_bound(T + 1, T + 1 + tot, q, cmp) - T - 1;
    return ((q - T[l]) & (T[l % (tot) + 1] - T[l])) <= 0;
}

ll n, m, q;

int main() {
    read(n, m, q);
    A.creat(n, 1);
    B.creat(m, -1);
    minkowski();
    convexhull(C, T, tot, k);
    for (ll i = (--tot); i > 0; i--)T[i] = T[i] - st;
    while (q--) {
        read(Q);
        printf("%lld\n", (ll) hullcheck(Q - st));
    }
    return 0;
}
