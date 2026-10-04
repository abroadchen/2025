//
// Created by Psy.C on 2026/10/4.
//
/**
qq[top]：当前 DFS 的访问栈/访问序列，top 是栈顶（当前深度）。qq[1] 是起点，qq[k] 是第 k 步访问的节点。
q[rt][y]：以 rt 为起点的、目标（终点）为 y 的所有询问，每个元素是 (k, id)——询问要求第 k 步，id 是询问编号。
vis[]：本轮 DFS 中该点是否已访问过（用于 DFS 扩展）。
vis2[]：该点是否已从其出边"返回"（出边的 DFS 已完成）‍，用于识别"当前正在沿反向/回边行走"。
cnt[y]：某节点 y 作为"回边目标"被访问的次数计数。
tmp：当前"回边计数器"的总和
二维数组 vector<ii> q[n+1][n+1]，按 x（起点）和 y（终点）双键存。这样在处理"以 x 为起点的所有询问"时，只关心 q[x][*]
对每个节点 i 作为起点，重置所有状态，做一次 DFS。这跟上一段代码很像——每个起点都要完整 DFS 一次。复杂度 O(n × (n+m)) 量级
qq 记录访问越深：qq[++top] = x，所以 qq[1] 是根，qq[k] 是 DFS 中第 k 个被访问的节点。这正是询问要的答案来源。

tmp 的用途——"当前是否处在不稳定（回边导致的非树边）路径上"：

当 DFS 遇到一条回边（y 已访问但 y 的出边还没完成，即 vis2[y]==0 且 vis[y]==1），说明进入了"非 DFS 树边区域"。
tmp 统计当前栈中"已进入回边区域"的累积次数。只有当 tmp==0（当前路径完全在 DFS 树上、稳定）时，才把挂在当前点上的询问的答案设为 qq[kk]。
因为如果某条路径经过了回边，那么"第 k 步是哪个节点"可能会依赖 DFS 的具体回溯顺序而不唯一/不明确，所以此时不回答（保持 -1）。
cnt 与出栈时的回退：节点 x 可能作为回边目标被多个祖先累加 cnt[x]；当 DFS 离开 x（--top）后，要把 x 的贡献从 tmp 里减去（tmp -= cnt[x]），并把 cnt[x] 清零、标记 vis2[x]=1。

这保证了 tmp 准确反映"当前 DFS 栈中，还有多少层是从回边进入的"。

vis2 的作用——区分"完成分支"与"可再走的边"：vis2[y] 表示 y 的所有出边分支都已遍历完。若 vis2[y] 为真则跳过 y（不重复进入已完成的子树）；这保证每条边在 DFS 树意义上只走一次，避免死循环。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 3e3+5, M = 4e5+5;

int qq[N], top, tmp, rt, ans[M], cnt[N];
vector<ii> q[N][N];
vector<int> a[N];
bool vis[N], vis2[N];
void dfs(int x) {
    qq[++top] = x;//记录：第 top 步访问到了 x
    if (!tmp) {//只有当"当前没有未决的回边"时才回答询问
        for (auto &[fst, snd] : q[rt][x]) {//挂在 (rt, x) 上、终点是 x 的询问
            int kk = fst, id = snd;
            if (kk <= top) ans[id] = qq[kk];
        }
    }
    for (int y : a[x]) {//遍历 x 的每条出边
        if (vis2[y]) continue;//y 的出边已完成，跳过（避免回溯到已完成分支）
        if (!vis[y]) vis[y] = 1, dfs(y);//未访问 → 正常深搜下去
        else ++tmp, cnt[y]++;//已访问 → 这是"回边"，进入已访问区，tmp 累加
    }
    --top;//离开 x，弹出
    tmp -= cnt[x];//离开 x 时，把 x 贡献的回边数从 tmp 中扣掉
    cnt[x] = 0; vis2[x] = 1;//清除计数、标记 x 的出边已完成
}

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y; a[x].push_back(y);
    }
    for (int i = 1; i <= n; ++i) ranges::sort(a[i]);
    for (int i = 1, x, y, z; i <= k; ++i) {
        cin >> x >> y >> z; q[x][y].emplace_back(z, i);
        ans[i] = -1;
    }
    for (int i = 1; i <= n; ++i) {
        tmp = 0, rt =  i, top = 0;
        for (int j = 1; j <= n; ++j) vis[j] = vis2[j] = 0;
        dfs(i);
    }
    for (int i = 1; i <= k; ++i) cout << ans[i] << '\n';
    return 0;
}