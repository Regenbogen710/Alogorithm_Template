#include<bits/stdc++.h>
#define rep(i,j,k) for(ll i=j;i<=k;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

namespace F {
    const ll N = 1e3 + 10, M = 2e5 + 10, INF = 0x3ffffffffff; // 若边数较多可增大 M
    ll s, t, n, m, to[M], nxt[M], cap[M], pre[M], head[N], h[N], now[N], cnt;
    ll balance[N], sum_need;  // 用于上下界
    ll SS, TT;                // 超级源、超级汇

    // ---------- 费用流相关 ----------
    ll cost[M];               // 边单位费用
    ll total_l_cost;          // 所有下界固定费用之和 (用于上下界费用流)
    ll dis[N], vis[N];        // SPFA
    ll pre_node[N], pre_edge[N]; // 记录增广路
    ll flow[N];               // 可增广流量
    queue<ll> q_spfa;

    void setup(ll sn, ll tn) {
        s = sn; t = tn;
    }

    // 无费用版本的 tlink
    void tlink(ll u, ll v, ll wei, ll fir) {
        to[++cnt] = v;
        cap[cnt] = wei;
        cost[cnt] = 0;        // 重要：兼容费用流环境
        nxt[cnt] = head[u];
        pre[cnt] = fir;
        head[u] = cnt;
    }
    void link(ll u, ll v, ll w) {
        tlink(u, v, w, cnt + 2);
        tlink(v, u, 0, cnt);
    }

    // 有费用版本的 tlink
    void tlink(ll u, ll v, ll wei, ll c, ll fir) {
        to[++cnt] = v;
        cap[cnt] = wei;
        cost[cnt] = c;
        nxt[cnt] = head[u];
        pre[cnt] = fir;
        head[u] = cnt;
    }
    void link(ll u, ll v, ll w, ll c) {
        tlink(u, v, w, c, cnt + 2);
        tlink(v, u, 0, -c, cnt);
    }

    // 原 Dinic BFS/DFS
    bool bfs() {
        queue<ll> q;
        q.emplace(s);
        memset(h, 0, sizeof(h));
        h[s] = 1; now[s] = head[s];
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            if (u == t) return true;
            for (ll i = head[u]; i; i = nxt[i]) {
                if (cap[i] && !h[to[i]]) {
                    now[to[i]] = head[to[i]];
                    h[to[i]] = h[u] + 1;
                    q.emplace(to[i]);
                }
            }
        }
        return false;
    }

    ll dfs(ll u, ll flow) {
        if (u == t) return flow;
        ll ret = flow;
        for (ll i = now[u]; i && ret; i = nxt[i]) {
            now[u] = i;
            if (cap[i] && h[to[i]] == h[u] + 1) {
                ll temp = dfs(to[i], (cap[i] < ret) ? cap[i] : ret);
                if (!temp) h[to[i]] = 0;
                ret -= temp;
                cap[i] -= temp, cap[pre[i]] += temp;
            }
        }
        return flow - ret;
    }

    ll solve() {
        ll maxflow = 0, temp = 0;
        while (bfs()) while ((temp = dfs(s, INF))) maxflow += temp;
        return maxflow;
    }

    // SPFA 找最短费用路 (用于最小费用流)
    bool spfa() {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[s] = 0; vis[s] = 1; flow[s] = INF;
        while (!q_spfa.empty()) q_spfa.pop();
        q_spfa.emplace(s);
        while (!q_spfa.empty()) {
            ll u = q_spfa.front(); q_spfa.pop();
            vis[u] = 0;
            for (ll i = head[u]; i; i = nxt[i]) {
                if (cap[i] && dis[to[i]] > dis[u] + cost[i]) {
                    dis[to[i]] = dis[u] + cost[i];
                    pre_node[to[i]] = u;
                    pre_edge[to[i]] = i;
                    flow[to[i]] = min(flow[u], cap[i]);
                    if (!vis[to[i]]) {
                        vis[to[i]] = 1;
                        q_spfa.emplace(to[i]);
                    }
                }
            }
        }
        return dis[t] != 0x3f3f3f3f3f3f3f3fLL;
    }

    // 最小费用流 (多次增广直到无路)
    pair<ll, ll> min_cost_flow(ll _s, ll _t) {
        setup(_s, _t);
        ll total_flow = 0, total_cost = 0;
        while (spfa()) {
            ll add = flow[t];
            total_flow += add;
            total_cost += add * dis[t];
            for (ll u = t; u != s; u = pre_node[u]) {
                ll e = pre_edge[u];
                cap[e] -= add;
                cap[pre[e]] += add;
            }
        }
        return {total_flow, total_cost};
    }

    // 最大费用流 (费用取反后用 min_cost_flow)
    pair<ll, ll> max_cost_flow(ll _s, ll _t) {
        for (ll i = 1; i <= cnt; i++) cost[i] = -cost[i];
        auto res = min_cost_flow(_s, _t);
        for (ll i = 1; i <= cnt; i++) cost[i] = -cost[i];
        return {res.first, -res.second};
    }

    // ---------- 上下界扩展 (无费用) ----------
    void clear() {
        memset(head, 0, sizeof(head));
        memset(balance, 0, sizeof(balance));
        cnt = 0;
        sum_need = 0;
        total_l_cost = 0;   // 重置下界费用累计
    }

    void add_edge(ll u, ll v, ll l, ll r) {
        balance[u] -= l;
        balance[v] += l;
        link(u, v, r - l);
    }

    bool build_feasible(ll n, ll _s, ll _t, bool has_source) {
        SS = n + 1, TT = n + 2;
        for (ll i = 1; i <= n; i++) {
            if (balance[i] > 0) {
                link(SS, i, balance[i]);
                sum_need += balance[i];
            } else if (balance[i] < 0) {
                link(i, TT, -balance[i]);
            }
        }
        if (has_source) {
            add_edge(_t, _s, 0, INF);  // 下界0，不影响
        }
        return true;
    }

    bool feasible_flow(ll n) {
        clear();
        build_feasible(n, 0, 0, false);
        setup(SS, TT);
        ll flow = solve();
        return flow == sum_need;
    }

    ll feasible_flow(ll n, ll _s, ll _t) {
        clear();
        build_feasible(n, _s, _t, true);
        setup(SS, TT);
        ll flow = solve();
        if (flow != sum_need) return -1;
        for (ll i = head[_t]; i; i = nxt[i]) {
            if (to[i] == _s) {
                return cap[pre[i]];
            }
        }
        return -1;
    }

    ll max_flow_bound(ll n, ll _s, ll _t) {
        setup(_s, _t);
        return solve();
    }

    ll min_flow_bound(ll n, ll _s, ll _t) {
        ll base_flow = feasible_flow(n, _s, _t);
        if (base_flow == -1) return -1;
        for (ll i = head[_t]; i; i = nxt[i]) {
            if (to[i] == _s) {
                cap[i] = 0;
                cap[pre[i]] = 0;
                break;
            }
        }
        setup(_t, _s);
        ll back_flow = solve();
        return base_flow - back_flow;
    }

    // ---------- 上下界费用流扩展 ----------
    // 带费用的添边（自动累计下界固定费用）
    void add_edge(ll u, ll v, ll l, ll r, ll c) {
        balance[u] -= l;
        balance[v] += l;
        total_l_cost += l * c;          // 记录下界必须的费用
        link(u, v, r - l, c);
    }

    bool build_cost_feasible(ll n, ll _s, ll _t, bool has_source) {
        SS = n + 1, TT = n + 2;
        for (ll i = 1; i <= n; i++) {
            if (balance[i] > 0) {
                link(SS, i, balance[i], 0);
                sum_need += balance[i];
            } else if (balance[i] < 0) {
                link(i, TT, -balance[i], 0);
            }
        }
        if (has_source) {
            add_edge(_t, _s, 0, INF, 0);  // 下界0，费用0
        }
        return true;
    }

    // 有源汇最小费用可行流
    pair<ll, ll> min_cost_feasible_flow(ll n, ll _s, ll _t) {
        // 注意：外部必须先 clear() 并 add_edge(u,v,l,r,c)
        build_cost_feasible(n, _s, _t, true);
        auto res = min_cost_flow(SS, TT);
        if (res.first != sum_need) return {-1, -1};
        return {res.first, res.second + total_l_cost};
    }

    // 有源汇最小费用最大流
    pair<ll, ll> min_cost_max_flow_bound(ll n, ll _s, ll _t) {
        auto base = min_cost_feasible_flow(n, _s, _t);
        if (base.first == -1) return {-1, -1};
        auto extra = min_cost_flow(_s, _t);
        return {base.first + extra.first, base.second + extra.second};
    }

    // 有源汇最大费用可行流
    pair<ll, ll> max_cost_feasible_flow(ll n, ll _s, ll _t) {
        // 临时取反费用
        for (ll i = 1; i <= cnt; i++) cost[i] = -cost[i];
        total_l_cost = -total_l_cost;   // 下界费用也要取反（稍后恢复）
        auto res = min_cost_feasible_flow(n, _s, _t);
        total_l_cost = -total_l_cost;
        for (ll i = 1; i <= cnt; i++) cost[i] = -cost[i];
        if (res.first == -1) return {-1, -1};
        return {res.first, -res.second};
    }

    // 有源汇最大费用最大流
    pair<ll, ll> max_cost_max_flow_bound(ll n, ll _s, ll _t) {
        auto base = max_cost_feasible_flow(n, _s, _t);
        if (base.first == -1) return {-1, -1};
        auto extra = max_cost_flow(_s, _t);
        return {base.first + extra.first, base.second + extra.second};
    }
}

// ---------- 示例 ----------
ll n, m, s, t, u, v, l, r, c;
int main() {
    // 读入（示例为无费用上下界最大流）
    scanf("%lld %lld %lld %lld", &n, &m, &s, &t);
    F::clear();
    rep(i, 1, m) {
        scanf("%lld %lld %lld %lld", &u, &v, &l, &r);
        F::add_edge(u, v, l, r);
    }
    ll f = F::feasible_flow(n, s, t);
    if (f == -1) {
        printf("NO feasible flow\n");
    } else {
        printf("Max flow: %lld\n", F::max_flow_bound(n, s, t));
    }
    return 0;
}