#include<bits/stdc++.h>
//#define putchar putchar_unlocked
//static char *p1,*p2,buf[1<<26];
//#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<26,stdin),p1==p2)?EOF:*p1++)
using namespace std;

typedef long long ll;

inline bool read(ll &x) {
    x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    if (f)x = -x;
}

inline void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9)write(x / 10);
    putchar(x % 10 ^ 48);
}

const ll INF = 0x3effffff;
const ll N = 1e6 + 10;
const ll M = 2e4 + 10;
const double eps = 1e-8;

ll n;

inline ll sgn(double x) {
    if (x > eps)return 1;
    if (x + eps < 0)return -1;
    return 0;
}

inline ll cmpbig(double x,double y) {
    return sgn(x - y);
}

inline ll cmpsma(double x,double y) {
    return sgn(y - x);
}

struct point2 {
    double x, y;

    point2() {}
    point2(double x, double y) :x(x), y(y) {}
    inline void read() { scanf("%lf%lf", &x, &y); }
    inline void write() { printf("%f %f\n", x, y); }
    inline point2 operator +(const point2 B) { return point2(x + B.x, y + B.y); }
    inline point2 operator -(const point2 B) { return point2(x - B.x, y - B.y); }
    inline point2 operator *(const double k) { return point2(x * k, y * k); }
    inline point2 operator /(const double k) { return point2(x / k, y / k); }
    inline bool operator ==(const point2 B) { return sgn(x - B.x) == 0 && sgn(y - B.y) == 0; }
    inline bool operator <(const point2 B) { return sgn(x - B.x) == 1 || (sgn(x - B.x) == 0 && sgn(y < B.y)); }
};

typedef point2 vector2;
inline double dot(const vector2 A, const vector2 B) { return A.x * B.x + A.y * B.y; }
inline double cross(const vector2 A, const vector2 B) { return A.x * B.y - A.y * B.x; }
inline double distance(const vector2 A) { return sqrt(A.x * A.x + A.y * A.y); }

struct hull {
    point2 p[N];
    point2 Hull[N];
    ll len;

    inline void read(ll n) {
        for ( ll i = 1; i <= n; i++)p[i].read();
        sort(p + 1, p + 1 + n);
    }

    inline void write() { for (ll i = 1; i <= len; i++) Hull[i].write(); }

    inline ll creat(ll n) {
        ll pos = 3;
        Hull[1] = p[1];
        Hull[2] = p[2];
        for (ll i = 3; i <= n; i++) {
            while (pos > 2 && sgn(cross(Hull[pos - 1] - Hull[pos - 2], p[i] - Hull[pos - 1])) == 1)pos--;
            Hull[pos] = p[i];
            pos++;
        }
        for (ll i = n - 1; i >= 1; i--) {
            while (pos > 2 && sgn(cross(Hull[pos - 1] - Hull[pos - 2], p[i] - Hull[pos - 1])) == 1)pos--;
            Hull[pos] = p[i];
            pos++;
        }
        len = pos - 2;
        p[len + 1] = p[1];
        return pos - 2;
    }

    inline double aera() {
        double aera = 0;
        for (ll i = 1; i <= len; i++) {
            aera += cross(Hull[i], Hull[i + 1]);
        }
        return aera / 2;
    }

    inline double dis() {
        double dis = 0;
        for (ll i = 1; i <= len; i++) {
            dis += distance(Hull[i] - Hull[i + 1]);
        }
        return dis;
    }
} hull;

int main() {
    read(n);
    hull.read(n);
    //	for(reg ll i=1;i<=n;i++){
    //		printf("%f ",cross(hull.p[(i+2)]-hull.p[(i+1)%n],p[]))
    //	}
    hull.creat(n);
    //	hull.write();
    printf("%.2f", hull.dis());
}

/*
4
4 8
4 12
5 9.3
7 8
*/
