#include<bits/stdc++.h>
#define rep(i,j,k) for(ll i=j;i<=k;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

namespace F {
    const ll N = 1e3 + 10, M = 2e5 + 10, INF = 0x3ffffffffff; // 注意 M 需扩大，因为会添加超级源汇的边
    ll s, t, n, m, to[M], nxt[M], cap[M], pre[M], head[N], h[N], now[N], cnt;
    ll balance[N], sum_need;  // 用于上下界
    ll SS, TT;                // 超级源、超级汇

    void setup(ll sn, ll tn) {
        s = sn;
        t = tn;
    }

    void tlink(ll u, ll v, ll wei, ll fir) {
        to[++cnt] = v;
        cap[cnt] = wei;
        nxt[cnt] = head[u];
        pre[cnt] = fir;
        head[u] = cnt;
    }

    void link(ll u, ll v, ll w) {
        tlink(u, v, w, cnt + 2);
        tlink(v, u, 0, cnt);
    }

    bool bfs() {
        queue<ll> q;
        q.emplace(s);
        memset(h, 0, sizeof(h));
        h[s] = 1;
        now[s] = head[s];
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
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

    // ---------- 上下界扩展 ----------
    void clear() { // 清空网络，准备新图
        memset(head, 0, sizeof(head));
        memset(balance, 0, sizeof(balance));
        cnt = 0;
        sum_need = 0;
    }

    // 添加有上下界的边 u->v，流量限制 [l, r]
    void add_edge(ll u, ll v, ll l, ll r) {
        balance[u] -= l;
        balance[v] += l;
        link(u, v, r - l);
    }

    // 构造超级源汇并检查可行流（内部使用）
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
            // 有源汇：连一条 t->s 下界 0、容量 INF 的边
            add_edge(_t, _s, 0, INF); // 这里会更新 balance，但下界为0不影响
        }
        return true;
    }

    // 无源汇可行流，返回可行流是否存在
    bool feasible_flow(ll n) {
        clear();
        // 假定边已经通过 add_edge 添加好了
        build_feasible(n, 0, 0, false);
        setup(SS, TT);
        ll flow = solve();
        return flow == sum_need;
    }

    // 有源汇可行流，返回可行流流量（不可行返回 -1）
    ll feasible_flow(ll n, ll _s, ll _t) {
        clear();
        build_feasible(n, _s, _t, true);
        setup(SS, TT);
        ll flow = solve();
        if (flow != sum_need) return -1;
        // 记录 t->s 边上的可行流流量
        for (ll i = head[_t]; i; i = nxt[i]) {
            if (to[i] == _s) { // 正向边 t->s
                return cap[pre[i]]; // 反向边容量即为已流过的流量
            }
        }
        return -1;
    }

    // 有源汇最大流（调用前需已存在可行流网络状态）
    ll max_flow_bound(ll n, ll _s, ll _t) {
        setup(_s, _t);
        return solve();
    }

    // 有源汇最小流
    ll min_flow_bound(ll n, ll _s, ll _t) {
        // 先求可行流
        ll base_flow = feasible_flow(n, _s, _t);
        if (base_flow == -1) return -1;
        // 删除 t->s 的 INF 边
        for (ll i = head[_t]; i; i = nxt[i]) {
            if (to[i] == _s) {
                cap[i] = 0;            // 正向边置0
                cap[pre[i]] = 0;       // 反向边置0
                break;
            }
        }
        // 从 t 到 s 跑最大流，退回流量
        setup(_t, _s);
        ll back_flow = solve();
        return base_flow - back_flow;
    }
}

ll n, m, s, t, u, v, l, r;
int main() {
    scanf("%lld %lld %lld %lld", &n, &m, &s, &t);
    F::clear(); // 初始化
    rep(i, 1, m) {
        scanf("%lld %lld %lld %lld", &u, &v, &l, &r);
        F::add_edge(u, v, l, r);
    }
    // 输出最大流（示例）
    ll f = F::feasible_flow(n, s, t);
    if (f == -1) {
        printf("NO feasible flow\n");
    } else {
        printf("Max flow: %lld\n", F::max_flow_bound(n, s, t));
    }
    return 0;
}