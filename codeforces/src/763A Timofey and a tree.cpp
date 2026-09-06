//
// Created by Psy.C on 2026/9/6.
//
/**
f[N]：标记数组，用于记录子树是否满足某种“同质性”条件（后文详述）。
a[N]：存储每个节点的属性值（如颜色、数字等）。
G[N]：邻接表，用于存储树的边信息（无向图）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+7;

int f[N], a[N];
vector<int> G[N];
//遍历整棵树，并标记每个节点是否满足其子树是“单色”且与父节点相同的条件
void dfs(int u, int fa) {
    f[u] = 1;//默认当前节点符合条件
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == fa) continue;//跳过父节点，防止回环
        dfs(v, u);//递归处理子节点
        //若子节点不符合( f[v] != 1 )或属性不同(a[u] != a[v])，则当前节点不符合
        if (f[v] != 1 || a[u] != a[v]) f[u] = 0;
    }
}

//在树中寻找一个特殊的根节点，使得除了最多一个分支外，其余所有子树都满足第一轮 DFS 的“单色”条件
int dfs2(int u, int fa, int lst) {
    //c1: 满足f=1的子树数量, c2: 同色子树数量, nxt: 唯一不满足的子节点
    int c1 = 0, c2 = 0, nxt = 0;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == fa) continue;
        if (f[v] == 1) {//子树是单色的
            c1++;
            if (a[u] == a[v]) c2++;//且颜色相同
        } else nxt = v;//记录唯一一个不满足的子树
    }
    int num = G[u].size();//当前节点的总度数
    if (u != 1) num--;//若不是根节点，则去掉父亲这条边
    //若除父亲外，所有子树都满足f=1，说明当前节点就是答案
    if (c1 == num) return u;
    //若除父亲外，只有一条边不满足，但它的颜色与父亲相同
    if (c2 == num-1 && a[u] == lst) {
        int x = dfs2(nxt, u, a[u]);//继续向下探索那个不满足的子树
        if (x != -1) return x;//找到合法根节点
    }
    return -1;
}
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        G[x].push_back(y); G[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dfs(1, -1);//构建 f[] 标记
    int ans = dfs2(1, -1, a[1]);//尝试找根
    if (ans != -1) cout << "YES\n" << ans << '\n';
    else cout << "NO\n";
    return 0;
}