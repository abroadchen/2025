//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
a 是实际存数据的最大堆；b 存已标记要删除的元素。del 不真的删，只往 b 塞并更新计数器；
cle() 负责把 a 和 b 顶部的"同名已删除元素"对着一并弹掉（真删除）。
pop/top/empty 都先 cle 再操作——实现了一个"支持快速删除并取最大"的堆
to 存储邻接表，cmp 把所有邻接表按邻居点的度降序排序（这样遍历时可提前 break）。
ds[p] 是点 p 的度。
del(u)：删除点 u，把与它相连、且度 > md 的邻居 p 的边权 z 压入 q[p]。因为邻接表已降序排序，遇到度 ≤ md 就 break
dp[now][0] / dp[now][1] 是这个点作为根，在"父边是否计入/留下名额"两种状态下的最优答案。
对每个子节点算"多选一条边的增量收益 t"；负收益直接采用低位，正收益放进可删堆里按需挑选最划算的（贪心）。
结尾的 push/del 是恢复现场，保证回溯时堆状态干净（树形 DP 的常用技巧）
按度把点分组存入 h[度]，并维护 nxt[i]（下一个还有点的更大度数）用于快速跳跃。
对每个阈值 md：先删除"度恰好 = md"的点（把对应边权塞进邻居堆），再对度 > md 的未访问点跑 dfs 并累加，输出该 md 的答案。
这是经典的按度数从大到小扫描（类似"删点 + 度数阈值"的离线解法），总体复杂度多次扫描可控。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

constexpr int N = 25e4+10;

struct node {
    ll sz, sum;//堆内有效元素个数 sz、有效元素和 sum
    priority_queue<ll> a, b;//a=主堆（实际元素），b=延迟删除堆
    void push(ll u) { a.push(u), sz++, sum += u; }
    void del(ll u) { b.push(u), sz--, sum -= u; }//标记删除（延迟）
    void cle() {
        for (; !a.empty() && !b.empty() && a.top() == b.top(); a.pop(), b.pop()) {}
    }
    void pop() { cle(), sum -= a.top(), a.pop(), sz--; }//真正弹出最大元素
    bool empty() { cle(); return a.empty(); }
    ll top() { cle(); return a.top(); }
} q[N];

ll ds[N];
inline bool cmp(pll u, pll v) { return ds[u.first] > ds[v.first]; }

vector<pll> to[N];//邻接表（目标点, 边权）
ll md;
inline void del(ll u) {
    ll i, p, z;
    for (i = 0; i < to[u].size(); i++) {
        p = to[u][i].first; z = to[u][i].second;
        if (ds[p] <= md) break;//邻居度 ≤ md，则停止（后续都更小）
        q[p].push(z);
    }
}

ll vis[N], dp[N][2];
vector<ll> use, g;
void dfs(ll now, ll lst) {
    ll i, j, p, z, cnt = ds[now]-md, res = 0;
    vis[now] = md;//标记本次已访问（用阈值做时间戳）
    for (; q[now].sz > ds[now]-md; q[now].pop()) {}//把堆里多于 cnt 的元素挤掉
    for (i = 0; i < to[now].size(); i++) {
        p = to[now][i].first;
        if (ds[p] <= md) break;//度 ≤ md 不用处理
        if (p == lst) continue;//跳过父节点
        dfs(p,now);//递归子树
    }
    use.clear(); g.clear();
    for (i = 0; i < to[now].size(); i++) {
        p = to[now][i].first; z = to[now][i].second;
        if (ds[p] <= md) break;
        if (p == lst) continue;
        ll t = dp[p][1] + z - dp[p][0];//子树采用"较高态"的额外收益
        if (t < 0) { cnt--; res += dp[p][0] + t; continue; }//收益为负，直接采用低位状态
        res += dp[p][0]; q[now].push(t); use.push_back(t);// 收益为正，暂存进堆
    }
    for (; !q[now].empty() && q[now].sz > cnt; q[now].pop()) g.push_back(q[now].top());
    dp[now][0] = res + q[now].sum;//不单算本点/高位态
    for (; !q[now].empty() && q[now].sz > cnt-1; q[now].pop()) g.push_back(q[now].top());
    dp[now][1] = res + q[now].sum;//多留 1 个名额的低位态
    for (i = 0; i < g.size(); i++) q[now].push(g[i]);//恢复被临时挤掉的元素
    for (i = 0; i < use.size(); i++) q[now].del(use[i]);//删除本点这次推入的元素（恢复现场）
}

ll n, sum, nxt[N], ans;
vector<ll> h[N];
int main() {
    fast;
    cin >> n;
    ll i, p, z, o, j, t;
    for (i = 1; i < n; i++) {
        cin >> p >> z >> o;
        to[p].emplace_back(z,o); to[z].emplace_back(p,o);
        ds[p]++, ds[z]++, sum += o;//建树，统计度和边权和
    }
    //按度分组，邻接表降序
    for (i = 1; i <= n; i++) { h[ds[i]].push_back(i); ranges::sort(to[i], cmp); }
    for (i = n; i >= 1; i--) {//从大到小的"下一非空度数"
        if (!h[i+1].empty()) nxt[i] = i + 1;
        else nxt[i] = nxt[i+1];
    }
    cout << sum << ' ';
    for (md = 1; md < n; md++) {//枚举度数阈值 md
        ans = 0;
        for (i = 0; i < h[md].size(); i++) del(h[md][i]);
        for (i = md+1; i; i = nxt[i])//对度 > md 的点遍历（按 nxt 跳）
            for (j = 0; j < h[i].size(); j++) {
                t = h[i][j];
                if (vis[t] == md) continue;//已访问过直接跳过
                dfs(t,-1);//以 t 为根做 DP，累加答案
                ans += dp[t][0];
            }
        cout << ans << ' ';
    }
    return 0;
}