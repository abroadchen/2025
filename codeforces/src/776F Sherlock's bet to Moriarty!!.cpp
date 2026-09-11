//
// Created by Psy.C on 2026/9/11.
//
/**
mx[]：子树/外接部分中最大块大小（用于重心判断）。
sz[]：子树大小。
vis[]：点分治中标记已分治过的点。
R：当前找到的重心候选。
g[]：邻接表（存最终构建的树/图
求重心：dfs 遍历子树，统计每棵子树大小 sz[it]、更新 mx[id]（取各子树最大者与"除去该子树后的剩余部分 tot - sz[id]"的较大者），同时维护 R 为 mx 最小的结点——即树的重心。
tot 为当前分治块总大小
点分治主过程（分治建树 + 定深度）‍：
把当前重心 id 标记为已处理（vis[id]=1）。
对每个未处理邻点 it：dfs2 求其连通块大小，再 dfs 找到该块的重心 R，令 lb[R] = lb[id] + 1（深度 = 父重心深度 + 1），随后递归 dfs3(R) 处理子重心。
因此最终的 lb[i] = 结点 i 在点分治重心树中的深度（根重心深度 1）

读入 n 个点、m 个区间（每行 x y 表示一个区间 [x, y]，把区间两端拆成"开/关"事件：{端点, 1} 表示左端点、{端点, 0} 表示右端点），然后按端点排序。
s 是尚未被分入任何块的点的集合（初始 1..n）。
mx[0]=n 作为重心比较的初值
用单调栈 + 区间划分把每个"括号对/区间"对应的点收集成一个块 rg[cnt]：
遇到左端点（second==1）入栈 st；
遇到右端点 id，弹出栈顶左端点 l（利用 sort 后区间成对嵌套的性质，栈顶即配对），新建一个块 rg[++cnt]，把 l 与 id 放入；
然后从 s 中把 (l, id) 之间的所有尚未分配的点 *it 也加入该块并从 s 删除（upper_bound(l) 起、直到遇到 id）——这一步把区间内部的点并入该块。
注意 st 的配对依赖"区间按两端排序后，配对的左右端点相邻匹配"这一性质（类似括号匹配）
++m：额外新增一块（编号 m），把 s 里未被任何区间包裹的剩余点全部并入这一"外圈块"。
每个 rg[i] 排序后反转（使块内有点按逆序排列，配合下一步"相邻配对"）。
再把所有块按字典序排序 sort(rg+1, rg+m+1)——块可比较（vector），便于后续识别相交块
对每个块 rg[i]，遍历其内部相邻元素对 (y, x)（每对相邻点构成一条"弧/边"），若这对 (x,y) 出现在之前的其它块 it->second 中，说明当前块与那个块相交/包含，就在两块的编号间连一条边 g[i]。
跳过 (1, n) 和相邻点 x+1==y 这两种平凡情形（对应整圈与直接相邻，不构成有效建边）。
于是最终 g 表达了一个由各块构成的"相邻/相交"关系图（实际是把平面区间/环切成块，块间相邻则连边
点分治初始化：从结点 1 开始 dfs 求得整棵树重心 R，令根重心 lb[R]=1，再 dfs3(R) 递归分解整棵树，得到每个块/结点在点分治重心树中的深度 lb[]。
最后按块编号 1..m 输出各块深度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5;

int mx[N], sz[N], vis[N], R;
vector<int> g[N];
void dfs(int id, int fa, int tot) {
    mx[id] = 0, sz[id] = 1;
    for (int it : g[id]) {
        if (it == fa || vis[it]) continue;
        dfs(it, id, tot);
        sz[id] += sz[it], mx[id] = max(mx[id], sz[it]);
    }
    mx[id] = max(mx[id], tot-sz[id]);
    if (mx[R] > mx[id]) R = id;
}

//简单求子树大小 sz（供下一步求重心时用）
void dfs2(int id, int fa) {
    sz[id] = 1;
    for (int it : g[id]) {
        if (it != fa && !vis[it])
            dfs2(it, id), sz[id] += sz[it];
    }
}

int lb[N];
void dfs3(int id) {
    vis[id] = 1;
    for (int it : g[id]) {
        if (vis[it]) continue;
        dfs2(it, id);
        R = 0, dfs(it, id, sz[it]);
        lb[R] = lb[id]+1, dfs3(R);
    }
}

set<int> s;
ii p[N<<1];
int st[N], top;
vector<int> rg[N];
map<ii, int> mp;
int main() {
    fast;
    int n, m; cin >> n >> m; mx[0] = n;
    for (int i = 1; i <= n; ++i) s.insert(i);
    for (int i = 1, x, y, cnt=0; i <= m; ++i) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        p[++cnt] = {x, 1}, p[++cnt] = {y, 0};
    }
    sort(p+1, p+m*2+1);
    for (int i = 1, cnt=0; i <= m*2; ++i) {
        int id = p[i].first;
        if (p[i].second) { st[++top] = id; continue; }
        int l = st[top--];
        rg[++cnt].push_back(l), rg[cnt].push_back(id);
        while (true) {
            auto it = s.upper_bound(l);
            assert(it != s.end());
            if (*it == id) break;
            rg[cnt].push_back(*it), s.erase(it);
        }
    }
    m++;
    while (!s.empty()) rg[m].push_back(*--s.end()), s.erase(--s.end());
    for (int i = 1; i <= m; ++i) {
        ranges::sort(rg[i]);
        ranges::reverse(rg[i]);
    }
    sort(rg+1, rg+m+1);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < rg[i].size(); ++j) {
            int x = rg[i][j], y = j ? rg[i][j-1] : rg[i].back();
            if (x > y) swap(x, y);
            if (x == 1 && y == n || x + 1 == y) continue;
            auto it = mp.find({x, y});
            if (it == mp.end()) mp[{x, y}] = i;
            else g[it->second].push_back(i), g[i].push_back(it->second);
        }
    }
    dfs(1, 0, m), lb[R] = 1, dfs3(R);
    for (int i = 1; i <= m; ++i) cout << lb[i] << ' ';
    return 0;
}