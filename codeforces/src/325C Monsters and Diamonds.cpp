//
// Created by Psy.C on 2026/1/8.
//
/**
 * v标记访问状态，ins标记在递归栈中
 *e[N]：邻接表，存储图的边
 *ds[N], dp[N]：距离数组和动态规划数组
 *
 *dfs函数：深度优先搜索，计算DP值
 *标记x为已访问和在栈中
 *遍历x的所有邻接节点（结构化绑定）
 *如果距离过大，跳转到nxt
 *遍历当前节点的所有依赖
 *如果未访问，递归处理
 *如果在栈中或有环，标记-2
 *更新DP值
 *退出时取消栈中标记
 *
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100003
using namespace std;

struct node { ll c{}; vector<int> d; };

bool v[N], ins[N];
vector<node> e[N];
ll ds[N], dp[N];
void dfs(const int x) {
    v[x] = true, ins[x] = true; ll sm;
    for (const auto&[c, d] : e[x]) {
        for (const auto i : d) if (static_cast<double>(ds[i]) > 1e18) goto nxt;
        sm = 0;//用于求和
        for (const auto i : d) {//遍历当前节点的依赖列表d
            if (!v[i]) {
                dfs(i);
                if (dp[i] == -2) dp[x] = -2;//如果子节点有环，标记当前节点也有环
            } else if (ins[i] || dp[i] == -2) dp[x] = -2;
            sm += dp[i];
        }
        if (dp[x] == -2) break;
        dp[x] = min(max(dp[x], sm + c), 314000000ll);//取当前值和新值的最大值  限制最大值不超过
        nxt:;
    }
    ins[x] = false;
}


int main() {
    fast;
    int m, n, ed[N]; cin >> m >> n;//m个任务，n个节点
    ll c[N], d[N];//计数器和依赖数组
    vector<int> f[N];//前置条件图 依赖于节点i的任务
    priority_queue<pair<ll, int>> q;//最大堆 {距离，节点}
    for (int i = 1, x, k, a; i <= m; ++i) {
        cin >> x >> k; c[i] = k, ed[i] = x;//目标节点x和依赖数量k
        node s;
        for (int j = 0; j < k; ++j) {
            cin >> a;//读入依赖节点
            if (a != -1) s.d.push_back(a), f[a].push_back(i);//添加依赖关系 任务i依赖于节点a
            else d[i]++, f[0].push_back(i);//增加d[i](虚拟依赖)，添加到0的依赖
        }
        s.c = d[i];//设置节点的c值
        e[x].push_back(s);//添加到邻接表
    }
    memset(ds, 0x3f, sizeof(ds));
    q.emplace(0, 0); ds[0] = 0;//从0开始，距离为0
    while (!q.empty()) {
        const int u = q.top().second; q.pop();
        if (v[u]) continue; v[u] = true;
        for (const auto i : f[u]) {//遍历所有依赖于节点u的任务i
            d[i] += ds[u];//更新任务i的依赖时间
            if (!--c[i]) {//如果所有依赖都完成
                if (d[i] < ds[ed[i]]) {//如果找到更短路径，更新
                    ds[ed[i]] = d[i];
                    q.emplace(-d[i], ed[i]);//负值实现最小堆
                }
            }
        }
    }
    memset(v, 0, sizeof(v));//重置访问标记
    for (int i = 1; i <= n; ++i) if (static_cast<double>(ds[i]) < 1e18 && !v[i]) dfs(i);//对所有可达节点执行DFS
    for (int i = 1; i <= n; ++i) {
        if (static_cast<double>(ds[i]) > 1e18) cout << "-1 -1\n";
        else cout << min(ds[i], 314000000ll) << ' ' << dp[i] << '\n';//输出最短距离和DP值
    }
    return 0;
}