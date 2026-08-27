//
// Created by Psy.C on 2026/8/27.
//
/**
- vector<int> v[N] ： 树的邻接表 ， v[i] 存储节点 i 的所有相邻节点。
- l, r ：两个向量，分别存储配对的两列特殊节点（ l[i] 与 r[i] 配对）。
- int vis[N] ： 特殊节点标记数组 ， vis[x]=1 表示节点 x 是特殊节点。
- int rt ： 中心节点 ，最终找到的满足条件的树根

- 清空邻接表 v 的每个向量。
- 用 memset 将 vis 数组清零（ sizeof(vis) 直接计算整个数组大小，避免 memset 坑）。
- 清空 l 、 r 向量，重置 rt=0

全局变量 k ，表示需要配对的对数（特殊节点总数为 [ o bj ec tO bj ec t ] 2 k ）
返回以 x 为根的子树中 特殊节点的数量 。
- 参数 x ：当前节点。
- 参数 fa ：父节点（避免回溯）。
- int sum = vis[x] ? 1 : 0 ：若当前节点是特殊节点，初始 sum=1 ，否则 sum=0 。
- int len = v[x].size() ：当前节点的邻居数量，用于后续遍历子节点
- 遍历所有邻居，跳过父节点 fa 。
- 递归调用 ： sum += get_root(t, x) ，累加子树中的特殊节点数量。
- 提前返回 ： if (rt) return 0 ——一旦已经找到中心节点（ rt≠0 ），后续递归直接返回0， 剪枝优化 避免无用计算
- 判断中心节点条件 ：若当前子树的特殊节点数 sum ≥ k ，则 当前节点可能是中心节点 （但只会选深度最小的那个，因为递归是后序遍历，先处理子节点再处理父节点，子节点满足条件时父节点也一定满足）。
- rt = x ：将 rt 设为当前节点，注意递归回溯时子节点先满足条件，会覆盖父节点的设置，因此最终 rt 是 最靠近叶子的那个满足 sum ≥ k 的节点 （也称为树的「特殊节点中心」）。
- 返回 sum ：供父节点累加子树的特殊节点数

从中心节点 rt 出发进行DFS，将特殊节点 按发现顺序 分为两组：
- int L = l.size() ：当前 l 向量的大小。
- 分组规则 ：
  - 若 l 还没填满（ L < k ），将当前特殊节点加入 l 组。
  - 否则加入 r 组。
- 核心思想：DFS按子树递归顺序发现特殊节点，这样 l[i] 和 r[i] 会来自 不同的子树分支 ，保证路径互不重叠
递归遍历所有子树， fa 是父节点避免回溯。DFS的遍历顺序决定了 l 和 r 中的节点来自不同的子树

- int n ：全局变量，树的节点总数。
- while (cin >> n >> k) ：循环读取多组测试用例，每组包含节点数 n 和配对对数 k 。
- init() ：初始化/重置所有全局变量
- 循环 n-1 次（树有 n-1 条边）。
- 读入边的两个端点 a 和 b 。
- 双向加边： v[a].push_back(b); v[b].push_back(a); （无向树）
读入 [ o bj ec tO bj ec t ] 2 k 个特殊节点的编号，标记 vis[x] = 1
- get_root(1, -1) ：从节点1开始递归找中心节点。根的父节点设为 -1 （不存在的节点号）。
- dfs(rt, -1) ：从找到的中心节点 rt 出发DFS，将特殊节点分为 l 和 r 两组
- cout << "1\n" << rt << '\n' ：
- 第一行输出 1 （可能表示某种方案编号或YES）。
- 第二行输出中心节点 rt 。
- 配对输出 ：循环 k 次，每次输出三个节点：
- l[i] ：第 i 对配对的左边特殊节点。
- r[i] ：第 i 对配对的右边特殊节点。
- rt ：中心节点（固定不变）。
- 每对节点 (l[i], r[i], rt) 满足： l[i] 到 rt 的路径和 r[i] 到 rt 的路径除 rt 外互不重叠

- 时间复杂度 ： O(n) ，每个节点最多被访问2次（ get_root 一次， dfs 一次）。
- 空间复杂度 ： O(n) ，邻接表和标记数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

vector<int> v[N], l, r;
int vis[N], rt;
void init() {
    for (auto& i : v) i.clear();
    memset(vis, 0, sizeof(vis));
    l.clear(); r.clear(); rt = 0;
}

int k;
int get_root(int x, int fa) {
    int sum = vis[x] ? 1 : 0, len = v[x].size();
    for (int i = 0; i < len; ++i) {
        int t = v[x][i];
        if (t == fa) continue;
        sum += get_root(t, x);
        if (rt) return 0;
    }
    if (sum >= k) rt = x;
    return sum;
}

void dfs(int x, int fa) {
    if (vis[x]) {
        int L = l.size();
        if (L < k) l.push_back(x);
        else r.push_back(x);
    }
    int len = v[x].size();
    for (int i = 0; i < len; ++i) {
        int t = v[x][i];
        if (t == fa) continue;
        dfs(t, x);
    }
}

int n;
int main() {
    fast;
    while (cin >> n >> k) {
        init();
        for (int i = 0, a, b; i < n - 1; ++i) {
            cin >> a >> b;
            v[a].push_back(b); v[b].push_back(a);
        }
        for (int i = 0, x; i < 2*k; ++i) {
            cin >> x;
            vis[x] = 1;
        }
        get_root(1, -1); dfs(rt, -1);
        cout << "1\n" << rt << '\n';
        for (int i = 0; i < k; ++i)
            cout << l[i] << ' ' << r[i] << ' ' << rt << '\n';
    }
    return 0;
}