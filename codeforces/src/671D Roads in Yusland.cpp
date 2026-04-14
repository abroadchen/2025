//
// Created by Psy.C on 2026/4/13.
//
/**
t[x]: 左偏树节点，w为权值，ps为位置
tag[x]: 懒惰标记
push_up: 区间更新
ls[x], rs[x]: 左右儿子
push_down: 下传懒惰标记

左偏树合并操作
保证堆性质（小根堆）
维护左偏性质：len[ls[x]] >= len[rs[x]]
len[x]: 节点x到叶子的最短距离

head[N]: 树的邻接表头
dep[N]: 节点深度
rt[N]: 每个节点对应的左偏树根
cov[N]: 覆盖标记（差分数组）
Head[N]: 特殊边的邻接表头
tot: 节点编号计数器
ans: 答案

DFS遍历树
更新子节点深度
递归处理子树
合并左偏树
累加覆盖标记

如果非根节点且未被覆盖，输出-1并退出
将特殊边加入左偏树
弹出深度大于等于当前节点的无效节点
将当前最小值加入答案
将该节点权值减去最小值（相当于弹出）

读入树的边，构建邻接表
读入m条特殊边
使用差分数组标记覆盖范围
将特殊边添加到Head邻接表

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;

struct edge { int v, w, nxt; } a[N*3];

int cnt;
void add(int x, int y, int z, int *arr) {
    a[++cnt].v = y, a[cnt].w = z, a[cnt].nxt = arr[x], arr[x] = cnt;
}

struct node { int w, ps; } t[N];
int tag[N];
void push_up(int x, int y) { t[x].w += y, tag[x] += y; }
int ls[N], rs[N];
void push_down(int x) {
    int& v = tag[x];
    if (!v) return;
    if (ls[x]) push_up(ls[x], v);
    if (rs[x]) push_up(rs[x], v);
    v = 0;
}
int len[N];
int merge(int x, int y) {
    if (!x || !y) return x|y;
    push_down(x), push_down(y);
    if (t[x].w > t[y].w) swap(x, y);
    rs[x] = merge(rs[x], y);
    if (len[ls[x]] < len[rs[x]]) swap(ls[x], rs[x]);
    len[x] = len[rs[x]] + 1;
    return x;
}

int head[N], dep[N], rt[N], cov[N], Head[N], tot;
ll ans;
void dfs(int x, int lst) {
    for (int i = head[x]; i; i = a[i].nxt)
        if (a[i].v != lst) {
            dep[a[i].v] = dep[x] + 1;
            dfs(a[i].v, x);
            rt[x] = merge(rt[x], rt[a[i].v]);
            cov[x] += cov[a[i].v];
        }
    if (x != 1 && !cov[x]) cout << "-1\n", exit(0);
    for (int i = Head[x]; i; i = a[i].nxt) {
        t[++tot] = {a[i].w, a[i].v};
        rt[x] = merge(rt[x], tot);
    }
    while (rt[x] && dep[t[rt[x]].ps] >= dep[x]) {
        push_down(rt[x]);
        rt[x] = merge(ls[rt[x]], rs[rt[x]]);
    }
    ans += t[rt[x]].w, push_up(rt[x], -t[rt[x]].w);
}

int n, m, x, y, z;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        cin >> x >> y;
        add(x, y, 0, head); add(y, x, 0, head);
    }
    while (m--) {
        cin >> x >> y >> z;
        ++cov[x], --cov[y];
        add(x, y, z, Head);
    }
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}