// Created by regenbogen on 2023-09-13
// 星期三

#include <bits/stdc++.h>

#define rep(i, l, r) for(int i=(l);i<=(r);i++)
#define pre(i, r, l) for(int i=(r);i>=(l);i--)

using namespace std;
typedef long long ll;


ll Memory_begin;

namespace F {
    const ll N = 1e3 + 10, M = 2e5 + 10, inf = 0x7ffffffffff;
    ll head[N], to[M], nxt[M], cap[M], w[M], fri[M], cnt;
    ll dis[N], pre[N], flow[N], pres[N], s, t;

    inline void setup(ll ns, ll nt) {
        s = ns;
        t = nt;
    }

    inline void tlink(ll u, ll v, ll wei, ll Cap, ll pr) {
        to[++cnt] = v;
        cap[cnt] = Cap;
        fri[cnt] = pr;
        w[cnt] = wei;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    inline void link(ll u, ll v, ll cap, ll wei) {
        tlink(u, v, wei, cap, cnt + 2);
        tlink(v, u, -wei, 0, cnt);
    }

    ll spfa() {
        memset(dis, 0x3f, sizeof(dis));
        memset(pre, 0, sizeof(pre));
        bitset<N> inq;
        deque<ll> q;
        q.emplace_front(s);
        flow[s] = inf, dis[s] = 0, inq[s] = 1;
        while (!q.empty()) {
            if (dis[q.back()] < dis[q.front()])swap(q.back(), q.front());
            ll now = q.front();
            q.pop_front();
            inq[now] = 0;
            for (ll i = head[now]; i; i = nxt[i]) {
                if (cap[i] > 0 && dis[to[i]] > dis[now] + w[i]) {
                    pre[to[i]] = now;
                    pres[to[i]] = i;
                    dis[to[i]] = dis[now] + w[i];
                    flow[to[i]] = min(flow[now], cap[i]);
                    if (!inq[to[i]]) {
                        if (!q.empty() && dis[to[i]] <= dis[q.front()])q.emplace_front(to[i]);
                        else q.emplace_back(to[i]);
                        inq[to[i]] = 1;
                    }
                }
            }
        }
        return pre[t] != 0 ? flow[t] : -1;
    }

    inline pair<ll, ll> solve() {
        ll now = t, maxflow = 0, cost = 0, tflow = 0;
        while (~(tflow = spfa())) {
            now = t;
            while (now != s) {
                cap[pres[now]] -= tflow;
                cap[fri[pres[now]]] += tflow;
                now = pre[now];
            }
            maxflow += tflow;
            cost += tflow * dis[t];
        }
        return {maxflow, cost};
    }
}


ll clock_begin, Memory_end;

int main() {
    //    fprintf(stderr, "%.3lf MB\n", (&Memory_end - &Memory_begin) / 1048576.0);
    //    fprintf(stderr, "%.3lf Ms\n", (clock() - clock_begin) / 1000.0);
    return 0;
}

//Start at上午9:12
//End at 10:26
