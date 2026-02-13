//
// Created by Psy.C on 2026/2/13.
//
/**
dot[]：边的终点
val[]：边权
nxt[]：下一条边

找树的重心（使最大子树最小的节点）
siz[x]：以x为根的子树大小
mx[x]：删除x后最大连通块的大小
root：重心

从重心开始遍历整棵树
dis[x]：到重心的距离
be[x]：x属于哪个块
s[i]：第i个块包含的节点
block：块编号计数器

a：存储每个块的最小节点值 {块中最小节点值, 块编号}
b：存储每个块的大小信息 {块大小, 块编号}
num[N]：每个块的大小
将节点x连接到块y中的最小节点

时间复杂度：O(n log²n)
 */
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100002
#define ii pair<int,int>
using namespace std;

int cnt, head[N], dot[N<<1], nxt[N<<1], val[N<<1];
void add(const int u, const int v, const int w) {
    dot[++cnt] = v; val[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
}

int siz[N], mx[N], root, n;
void dfs(const int x, const int fa) {
    siz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        const int v = dot[i];
        if (v == fa) continue;
        dfs(v, x);
        siz[x] += siz[v];
        mx[x] = max(mx[x], siz[v]);//删除x后子树的最大大小
    }
    mx[x] = max(mx[x], n - siz[x]);//剩余的那部分（父亲方向的子树）
    if (mx[root] > mx[x]) root = x;
}

int be[N], block;
set<int> s[N];
ll ans, dis[N];
void dfs2(const int x, const int fa, const int blo) {
    //（不是第一轮），将x分配到块blo中 标记x属于blo块 将x插入blo块的集合
    if (blo) be[x] = blo, s[blo].insert(x);
    ans += dis[x] << 1;
    for (int i = head[x]; i; i = nxt[i]) {
        const int v = dot[i];
        if (v == fa) continue;
        dis[v] = dis[x] + val[i];//更新到v的距离
        if (blo) dfs2(v, x, blo);//继续在当前块中处理
        else dfs2(v, x, ++block);//(第一轮），创建新块（++block）并处理
    }
}

set<ii> a, b;
int num[N], res[N];
void link(const int x, const int y) {
    int t = *s[y].begin();//块y中的最小节点值
    b.erase({num[be[x]], be[x]});//删除x所在块和y块的信息
    b.erase({num[y], y});
    a.erase({t, y});//删除y块的最小值信息
    res[x] = t;//将x的结果设为t
    s[y].erase(t);//从y块中移除节点t
    //y块还有节点，插入新的最小值信息
    if (!s[y].empty()) a.insert({*s[y].begin(), y});
    --num[be[x]]; --num[y];//减少两个块的大小
    b.insert({num[be[x]], be[x]});//重新插入更新后的块大小信息到集合
    b.insert({num[y], y});
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    //防止0节点影响
    mx[0] = n; dfs(1, 0); dfs2(root, 0, 0);//从重心开始构建块结构
    s[0].insert(root);//将重心加入0号块
    for (int i = 0; i <= block; ++i) {
        a.insert({*s[i].begin(), i});
        num[i] = (int(s[i].size()) << 1);
        b.insert({num[i], i});
    }
    for (int i = 1; i <= n; ++i) {
        if (b.rbegin()->first == n - i + 1 && b.rbegin()->second != be[i] &&
            b.rbegin()->second != 0) link(i, b.rbegin()->second);
        else {
            auto it = a.begin();
            if (i != root && it->second == be[i]) ++it;
            link(i, it->second);
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i)
        cout << res[i] << " \n"[i==n];
    return 0;
}