#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 10;
ll n, tn, d, t[N], cnt[N];

struct node {
    ll x, y, z, cnt, ans;
    inline bool operator ==(const node &a) const { return x == a.x && y == a.y && z == a.z; }
} ts[N], s[N];

inline void add(ll pos, ll x) { for (ll i = pos; i <= d; i += (i) & (-i))t[i] += x; }

inline ll query(ll pos) {
    ll ans = 0;
    for (ll i = pos; i > 0; i -= (i & (-i)))ans += t[i];
    return ans;
}

inline bool cmp2(node i, node j) {return i.y < j.y || (i.y == j.y && i.x < j.x) || (i.x == j.x && i.y == j.y && i.z < j.z);}
inline bool cmp1(node i, node j) {return i.x < j.x || (i.x == j.x && i.y < j.y) || (i.x == j.x && i.y == j.y && i.z < j.z);}

void solve(ll l, ll r) {
    if (l == r)return;
    ll mid = (l + r) >> 1, i, j;
    solve(l, mid);
    solve(mid + 1, r);
    sort(s + l, s + mid + 1, cmp2);
    sort(s + mid + 1, s + r + 1, cmp2);
    for (i = mid + 1, j = l; i <= r; i++) {
        while (s[j].y <= s[i].y && j <= mid)add(s[j++].z, s[j].cnt);
        s[i].ans += query(s[i].z);
    }
    for (ll k = l; k < j; k++)add(s[k].z, -s[k].cnt);
}

int main() {
    scanf("%lld %lld", &tn, &d);
    for (ll i = 1; i <= tn; i++)ts[i].cnt = 1;
    for (ll i = 1; i <= tn; i++)scanf("%lld %lld %lld", &ts[i].x, &ts[i].y, &ts[i].z);
    sort(ts + 1, ts + 1 + tn, cmp1);
    for (ll i = 0; i < tn; i++) {
        if (!(ts[i] == ts[i + 1]))s[++n] = ts[i + 1];
        else s[n].cnt++;
    }
    solve(1, n);
    for (ll i = 1; i <= n; i++)cnt[s[i].ans + s[i].cnt - 1] += s[i].cnt;
    for (ll i = 0; i < tn; i++)printf("%lld\n", cnt[i]);
    return 0;
}
