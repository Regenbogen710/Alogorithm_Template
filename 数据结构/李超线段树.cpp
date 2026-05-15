#include<bits/stdc++.h>
using namespace std;
#define cout if(isdebug) cout
typedef long long ll;
typedef double db;

ll read() {
    ll x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        f |= ch == '-';
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? -x : x;
}

const bool isdebug = 1;
ll n, lastans, tot;
db x, x2, y, y2;
const db eps = 1e-9;
db unzipx(const ll num) { return (num + lastans - 1 + 39989) % 39989 + 1; }
db unzipy(const ll num) { return (num + lastans - 1 + 1000000000) % 1000000000 + 1; }

void update(const ll num) {
    lastans = num;
    return void();
}

ll sgn(const db num) { return (num > eps) ? 1 : (num + eps > 0) ? 0 : -1; }

namespace Segment {
    const ll N = 1e5 + 10;
    const db inf = 1e18;

    struct pi {
        db num;
        ll id;

        bool operator <(const pi &cmp) const {return sgn(cmp.num - num) == 1 || (sgn(cmp.num - num) == 0 && id > cmp.id);}
    };

    pi pmax(const pi a, const pi b) { return (a < b) ? b : a; }
    struct line {
        db k, b, l, r;
        ll id;
        db operator [](const ll &num) const { return (num <= r && num >= l) ? (num * 1.0 * k + b) : -inf; }
    } val[N << 1];

    ll L[N << 1], R[N << 2], ch[N][2], mid[N << 1], cnt, rt;

    void _build(ll &now, const ll l, const ll r) {
        now = ++cnt;
        L[now] = l;
        R[now] = r;
        val[now].r = -1;
        mid[now] = (l + r) >> 1;
        if (l == r)return void();
        _build(ch[now][0], l, mid[now]);
        _build(ch[now][1], mid[now] + 1, r);
        return void();
    }

    void inspre(const ll &now, line x) {
        if (x.l > R[now] || x.r < L[now])return void();
        if (x.l <= L[now] && R[now] <= x.r) {
            line temp = x;
            if (sgn(val[now][mid[now]] - temp[mid[now]]) == -1) swap(val[now], temp);
            if (L[now] == R[now]) return void();
            ll lres = sgn(val[now][L[now]] - temp[L[now]]);
            ll rres = sgn(val[now][R[now]] - temp[R[now]]);
            if (lres == -1 || (lres == 0 && val[now].id > temp.id))inspre(ch[now][0], temp);
            if (rres == -1 || (rres == 0 && val[now].id > temp.id))inspre(ch[now][1], temp);
            return void();
        }
        inspre(ch[now][0], x);
        inspre(ch[now][1], x);
        return void();
    }

    pi querypre(const ll &now, const ll &pos) {
        pi temp = {val[now][pos], val[now].id};
        if (R[now] == L[now])return temp;
        if (mid[now] >= pos)return pmax(temp, querypre(ch[now][0], pos));
        else return pmax(temp, querypre(ch[now][1], pos));
    }

    void build(ll l, ll r) {return _build(rt, l, r);}
    void ins(line &x) {return inspre(rt, x);}

    ll query(const ll &pos) {
        pi temp = querypre(rt, pos);
        return temp.id;
    }
}

using namespace Segment;

int main() {
    n = read();
    build(0, 4e5);
    for (ll i = 1; i <= n; i++) {
        if (read() == 0) {
            lastans = query((ll) unzipx(read()));
            printf("%lld \n", lastans);
        } else {
            x = unzipx(read());
            y = unzipy(read());
            x2 = unzipx(read());
            y2 = unzipy(read());
            line temp;
            if (x == x2)temp = line{0, max(y, y2), x, x, ++tot};
            else temp = line{(y2 - y) / (x2 - x), y - x * ((y2 - y) / (x2 - x)), min(x, x2), max(x, x2), ++tot};
            ins(temp);
        }
    }
    return 0;
}
