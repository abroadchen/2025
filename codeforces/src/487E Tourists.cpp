//
// Created by Psy.C on 2026/2/18.
//
/**
dfn[N]: DFS序 节点首次被访问的时间戳
low[N]: Tarjan算法中的low值 能到达的最早祖先
tot: 时间戳计数器
st[N]: 栈
tp: 栈顶指针
cnt: SCC计数器
g[N]: 原图
e[N]: 缩点后的树

找出原图的强连通分量（SCC）
将每个SCC缩成一个点，形成树结构
low[i] == dfn[x] 时发现一个SCC

cnt++: 新的SCC编号
e[cnt].push_back(x): 在SCC节点连接原节点x
e[x].push_back(cnt): 在原节点x连接SCC节点

d[x]: 深度
fa[x]: 父节点
siz[x]: 子树大小
son[x]: 重儿子
s[x]: 如果x是SCC节点，存储其子节点的值
找出重链（最大子树）

top[x]: x所在重链的顶部
id[x]: x的DFS序编号
idx: DFS序计数器
b[idx]: 线段树的叶子节点值
将树按重链剖分，连续编号

预处理：O(n)
查询：O(log²n)
修改：O(log n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5, inf = 1e9;

int dfn[N], low[N], tot, st[N], tp, cnt;
vector<int> g[N], e[N];
void tarjan(const int x) {
    dfn[x] = low[x] = ++tot, st[++tp] = x;
    for (const auto i : g[x]) {
        if (!dfn[i]) {//i还没被访问过
            tarjan(i);
            low[x] = min(low[x], low[i]);
            if (low[i] == dfn[x]) {// 发现一个强连通分量
                cnt++; e[cnt].push_back(x); e[x].push_back(cnt);
                for (; st[tp+1] != i; --tp)//弹出栈中属于当前SCC的节点
                    e[cnt].push_back(st[tp]), e[st[tp]].push_back(cnt);//建立双向连接
            }
        } else low[x] = min(low[x], dfn[i]);
    }
}

int d[N], fa[N], siz[N], son[N], n, a[N];
multiset<int> s[N];//每个SCC节点存储其子节点权值的有序多重集合
void dfs(const int x, const int f) {
    d[x] = d[f] + 1, fa[x] = f; siz[x] = 1;
    for (const auto i : e[x]) if (i^fa[x]) {//i不是父节点（异或判断不等于）
        dfs(i, x);
        if (x > n) s[x].insert(a[i]);//x是SCC节点，将子节点权值加入集合
        if (siz[i] > siz[son[x]]) son[x] = i;//找到最大的子树作为重儿子
        siz[x] += siz[i];//累加子树大小
    }
}

int top[N], id[N], idx, b[N];
void dfs2(const int x, const int tf) {
    top[x] = tf;//设置x所在重链的顶端
    id[x] = ++idx;//给x分配DFS序编号
    if (x <= n) b[idx] = a[x];//原节点，存储其权值
    else b[idx] = *s[x].begin();//SCC节点，存储最小权值
    if (son[x]) dfs2(son[x], tf);//优先处理重儿子，保持链的连续性
    for (const auto i : e[x])//遍历轻儿子
        if (i != fa[x] && i != son[x])
            dfs2(i, i);//递归处理轻儿子，新链从i开始
}

#define mid ((l+r)>>1)
int mn[N<<2];
void build(const int rt, const int l, const int r) {
    if (l == r) { mn[rt] = b[l]; return; }
    build(rt<<1, l, mid), build(rt<<1|1, mid+1, r);
    mn[rt] = min(mn[rt<<1], mn[rt<<1|1]);
}

void update(const int rt, const int l, const int r, const int x, const int num) {
    if (l > x || r < x) return;//当前区间不包含x
    if (l == r) { mn[rt] = num; return; }
    update(rt<<1, l, mid, x, num), update(rt<<1|1, mid+1, r, x, num);
    mn[rt] = min(mn[rt<<1], mn[rt<<1|1]);
}

int query(const int rt, const int l, const int r, const int L, const int R) {
    if (l > R || r < L) return inf;//当前区间与查询区间无交集
    if (l >= L && r <= R) return mn[rt];
    return min(query(rt<<1, l, mid, L, R), query(rt<<1|1, mid+1, r, L, R));
}

int get(int x, int y) {
    int res = inf;
    while (top[x] != top[y]) {//x和y不在同一条重链上
        if (d[top[x]] < d[top[y]]) swap(x, y);//让x成为深度更深的节点
        res = min(res, query(1, 1, cnt, id[top[x]], id[x]));//查询当前重链区间最小值
        x = fa[top[x]];//x跳到当前重链顶端的父节点
    }
    if (d[x] < d[y]) swap(x, y);//让x成为深度更深的节点
    res = min(res, query(1, 1, cnt, id[y], id[x]));//查询最后区间
    if (y > n) res = min(res, a[fa[y]]);//特殊处理
    return res;
}

inline int read() {
    char ch = getchar(); bool f = false; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = true;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f == 1) x = -x;
    return x;
}

int m, q, x, y;
int main() {
    n = read(), m = read(), q = read(); cnt = n;
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= m; ++i) {
        x = read(), y = read();
        g[x].push_back(y), g[y].push_back(x);
    }
    tarjan(1); dfs(1, 0); dfs2(1, 1); build(1, 1, cnt);
    for (int i = 1; i <= q; ++i) {
        char ch = getchar();
        while (ch != 'A' && ch != 'C') ch = getchar();//跳过无效字符
        x = read(), y = read();
        if (ch == 'A') printf("%d\n", get(x, y));
        else {
            if (fa[x]) {
                s[fa[x]].erase(s[fa[x]].find(a[x]));//从父节点集合中删除旧值
                s[fa[x]].insert(y);//插入新值
                update(1, 1, cnt, id[fa[x]], *s[fa[x]].begin());//更新线段树
            }
            a[x] = y;//更新权值
            update(1, 1, cnt, id[x], y);//更新线段树
        }
    }
    return 0;
}