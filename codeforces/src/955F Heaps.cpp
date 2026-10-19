//
// Created by Psy.C on 2026/10/19.
//
/**
N = 3e5+1：最大节点数上界。
son[u]：节点 u 的儿子个数（见主函数那里的计算）。
e[N]：邻接表（存树的无向边）。
mx[u]：一个以"深度/层级下标"存储的数组，mx[u][i] 表示 u 的子树中，第 i 层（到 u 距离为 i 的节点数相关）的某个最大值。它的语义是"子树第 i 层的最大'覆盖能力/节点计数'"。
dp[u]：dp[u][i] 表示 u 的子树中第 i 层的一个 DP 值（通常是该层所需的"站点数/代价/覆盖数"）。
sum[u]：节点 u 子树内累计的答案贡献和（启发式合并时维护的可变和）。
ans：全局答案。
mx 与 dp 都是"按层（深度 i）"存数组——这是树上"逐层计数/覆盖"类 DP 的典型结构
叶子（无儿子）特殊处理：

mx[u].resize(2, 1)：把 mx[u] 扩到 2 个元素（下标 0,1），值都设为 1。含义：叶子节点在第 0 层和第 1 层各贡献"1"。
sum[u] = 1：叶子子树累计和为 1。
ans += n：每个叶子对答案的贡献是 n。
返回
t：一个临时的"桶"数组，t[i] 收集 所有儿子的 dp[v][i]（第 i 层的 DP 值列表）。这用于后面算"第 i 层需要的最大的那些值之和"。
遍历每个儿子 v（排除父节点 p），先 dfs(v,u) 递归。
把儿子 v 的第 i 层 DP 值 dp[v][i] 放进桶 t[i]。
ms = 记录 mx[v] 数组最大的那个儿子（启发式合并的"重儿子"，即层数最深/数组最长的儿子）
t：一个临时的"桶"数组，t[i] 收集 所有儿子的 dp[v][i]（第 i 层的 DP 值列表）。这用于后面算"第 i 层需要的最大的那些值之和"。
遍历每个儿子 v（排除父节点 p），先 dfs(v,u) 递归。
把儿子 v 的第 i 层 DP 值 dp[v][i] 放进桶 t[i]。
ms = 记录 mx[v] 数组最大的那个儿子（启发式合并的"重儿子"，即层数最深/数组最长的儿子）
把其他（轻）儿子的 mx[v] 合并进 mx[u]，做"按层取最大值"：

遍历每个非重儿子 v。
对每一层 i：若 mx[v][i] > mx[u][i]（v 这层更大），则把差值累加进 sum[u] 并更新 mx[u][i]。
这样 mx[u] 就成了所有儿子在该层最大值的合并；sum[u] 同步维护了这个"最大值数组"对应的累计和
第 i 层的 DP 计算：

若桶 t[i] 中收集到的条目数 < i（第 i 层儿子不足 i 个），则 dp[u][i] = 2（一个基础下界）。
否则：nth_element 把第 i 大的放到倒数第 i 位（部分排序，O(size)），dp[u][i] = 第 i 大的值 + 1。也就是"该层取儿子里第 i 大的 dp 值再加 1"。
然后若 dp[u][i] > mx[u][i]，更新 mx[u][i] 并累加差值到 sum[u]
节点 u 对最终答案的贡献 = sum[u]（合并后的累计最大数组和）+ n （基准项）− (mx[u].size()-1)（数组长度的修正）

读 n，读 n-1 条边（这是一棵树）。
son[i] = e[i].size() - (i != 1)：儿子个数 = 度数 − 是否为根(1)。根节点（i==1）不减，其他节点减掉父节点那条边，得到"真正儿子数"。
dfs(1, 0)：从根 1 开始 DFS（父节点 0 表示无父）。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+1;

int son[N], n;
vector<int> mx[N], e[N], dp[N];
ll sum[N], ans;
void dfs(int u, int p) {
    if (son[u] == 0) return mx[u].resize(2, 1), sum[u] = 1, ans += n, void();
    vector<vector<int>> t(son[u]+1);
    int ms = 0;
    for (auto v : e[u]) if (v != p) {
        dfs(v, u);
        rep(i,1,min(son[v], son[u])) t[i].emplace_back(dp[v][i]);
        if (!ms || mx[v].size() > mx[ms].size()) ms = v;
    }
    dp[u].resize(son[u]+1);
    sum[u] = sum[ms], swap(mx[u], mx[ms]);
    if (mx[u].size() <= son[u]) mx[u].resize(son[u]+1);
    for (auto v : e[u]) if (v != p && v != ms) {
        rep(i,1,mx[v].size()-1) if (mx[v][i] > mx[u][i])
            sum[u] += mx[v][i] - mx[u][i], mx[u][i] = mx[v][i];
    }
    rep(i,1,son[u]) {
        if (t[i].size() < i) dp[u][i] = 2;
        else ranges::nth_element(t[i], t[i].end()-i), dp[u][i] = t[i][t[i].size()-i] + 1;
        if (dp[u][i] > mx[u][i]) sum[u] += dp[u][i] - mx[u][i], mx[u][i] = dp[u][i];
    }
    ans += sum[u] + n - int(mx[u].size()-1);
}


int main() {
    fast;
    cin >> n;
    rep(i,2,n) {
        int u, v; cin >> u >> v;
        e[u].emplace_back(v); e[v].emplace_back(u);
    }
    rep(i,1,n) son[i] = int(e[i].size()) - (i!=1); dfs(1, 0);
    cout << ans << '\n';
    return 0;
}