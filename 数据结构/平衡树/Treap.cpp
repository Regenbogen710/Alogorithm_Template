// Created by regenbogen on 23-8-22.
#include<bits/stdc++.h>
// #include<bits/extc++.h>
using namespace std;
typedef int ll;

inline ll read() {
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

inline void read(ll &x) { x = read(); }

template<typename T, typename... Args>
inline void read(T &x, Args &... args) {
    read(x);
    read(args...);
}

const ll N = 1e5 + 10;
mt19937 R(clock() ^ time(0));
inline ll rnd(ll l, ll r) { return R() % (r - l + 1) + l; }

namespace Treap {
    const ll N = 2e5 + 10;
    ll ch[N][2], val[N], v[N], siz[N], cnt, root;

    inline ll newnode(ll x) {
        v[++cnt] = rnd(1, 1e9);
        val[cnt] = x;
        siz[cnt] = 1;
        return cnt;
    }

    inline void pushup(ll now) { siz[now] = siz[ch[now][0]] + siz[ch[now][1]] + 1; }

    void split(ll now, ll x, ll &ch1, ll &ch2) {
        if (!now)return ch1 = 0, ch2 = 0, void();
        if (val[now] <= x) ch1 = now, split(ch[now][1], x, ch[now][1], ch2), pushup(ch1);
        else ch2 = now, split(ch[now][0], x, ch1, ch[now][0]), pushup(ch2);
    }

    ll merge(ll ch1, ll ch2) {
        if (!ch1 || !ch2)return ch1 | ch2;
        if (v[ch1] < v[ch2])ch[ch1][1] = merge(ch[ch1][1], ch2);
        else ch[ch2][0] = merge(ch1, ch[ch2][0]), swap(ch1, ch2);
        return pushup(ch1), ch1;
    }

    inline ll kth(ll now, ll k) {
        while (true) {
            if (siz[ch[now][0]] + 1 == k)return now;
            if (siz[ch[now][0]] + 1 < k)k -= siz[ch[now][0]] + 1, now = ch[now][1];
            else now = ch[now][0];
        }
    }

    inline void insert(ll x) {
        ll ch1, ch2;
        split(root, x, ch1, ch2);
        root = merge(merge(ch1, newnode(x)), ch2);
    }

    inline void del(ll x) {
        ll ch1, ch2, ch3, ch4;
        split(root, x, ch1, ch2);
        split(ch1, x - 1, ch3, ch4);
        ch4 = merge(ch[ch4][0], ch[ch4][1]);
        root = merge(merge(ch3, ch4), ch2);
    }

    inline ll rank_k(ll x) {
        return val[kth(root, x)];
    }

    inline ll query_rank(ll x) {
        ll ch1, ch2, ans;
        split(root, x, ch1, ch2);
        ans = siz[ch1] + 1;
        root = merge(ch1, ch2);
        return ans;
    }

    inline ll pre_num(ll x) {
        ll ch1, ch2, ans;
        split(root, x - 1, ch1, ch2);
        ans = val[kth(ch1, siz[ch1])];
        merge(ch1, ch2);
        return ans;
    }

    inline ll nxt_num(ll x) {
        ll ch1, ch2, ans;
        split(root, x, ch1, ch2);
        ans = val[kth(ch2, 1)];
        root = merge(ch1, ch2);
        return ans;
    }
}

ll n, opt;

int main() {
    read(n);
    while (n--) {
        read(opt);
        if (opt == 1)Treap::insert(read());
        else if (opt == 2)Treap::del(read());
        else if (opt == 3)printf("%d\n", Treap::query_rank(read() - 1));
        else if (opt == 4)printf("%d\n", Treap::rank_k(read()));
        else if (opt == 5)printf("%d\n", Treap::pre_num(read()));
        else if (opt == 6)printf("%d\n", Treap::nxt_num(read()));
    }
    return 0;
}
