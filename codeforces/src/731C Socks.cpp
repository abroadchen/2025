//
// Created by Psy.C on 2026/4/26.
//
/**
rk[i]: 节点 i 的秩（树的高度），用于优化并查集
fa[i]: 节点 i 的父节点，用于构建并查集树
初始化单个节点 x，设置其秩为0，父节点为自己
如果 x 不是根节点（x != fa[x]），则递归查找父节点，并将当前节点直接连接到根节点（路径压缩）
返回 x 所在集合的根节点
先找到 x 和 y 所在集合的根节点
如果已经在同一集合，直接返回
否则根据秩的大小决定合并方向：将秩小的树合并到秩大的树上
如果两棵树秩相同，则任意合并，并增加新根的秩

n: 节点数量
m: 边的数量
k: 可能是颜色种类数（虽然代码中未使用）
a[i]: 节点 i 的颜色值
初始化并查集，每个节点都是独立的集合
遍历所有节点，将每个节点的颜色添加到其所在连通分量的向量中
find(i) 找到节点 i 所在集合的根节点，然后将颜色 a[i] 添加到对应向量中
遍历每个连通分量
如果连通分量只有一个或零个节点，跳过（不需要改变颜色）
清空计数器 mp
统计当前连通分量中每种颜色出现的次数，找出出现次数最多的颜色数量 mx
将连通分量中其他颜色都改为出现次数最多的颜色，需要改变的节点数为 v[i].size() - mx
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+7;

int rk[N], fa[N];
void init(int x) { rk[x] = 0; fa[x] = x; }

int find(int x) {
    if (x != fa[x]) return fa[x] = find(fa[x]);
    return fa[x];
}
void uni(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (rk[x] > rk[y]) fa[y] = x;
    else { fa[x] = y; rk[y]++; }
}

int n, m, k, a[N];
vector<int> v[N];///存储每个连通分量中的所有颜色值
map<int, int> mp;///连通分量中每种颜色出现的次数
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) { fa[i] = i; rk[i] = 0; }
    for (int i = 1; i <= n; ++i) cin >> a[i];//读入每个节点的颜色值
    for (int i = 1, x, y; i <= m; ++i) { cin >> x >> y; uni(x, y); }//将连接的节点合并到同一个集合中
    for (int i = 1; i <= n; ++i) v[find(i)].push_back(a[i]);
    int ans = 0;
    for (int i = 1, mx; i <= n; ++i) {
        if (v[i].size() <= 1) continue; mp.clear();
        mx = 0;
        for (int j : v[i]) {
            mp[j]++;
            mx = max(mx, mp[j]);
        }
        ans += v[i].size() - mx;
    }
    cout << ans << '\n';
    return 0;
}