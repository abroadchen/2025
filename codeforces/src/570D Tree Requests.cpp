//
// Created by Psy.C on 2026/3/13.
//
/**
左右子节点索引和异或值
tot：节点编号计数器
update函数：在线段树中更新位置x的值
如果节点不存在，创建新节点
对节点的值进行异或操作
递归更新左子树或右子树
t：查询结果
query函数：查询区间[L,R]的异或值
如果当前区间完全包含在查询区间内，更新结果并返回
否则递归查询左右子树

L,R：DFS序的进入和退出时间
T：每层的线段树根节点
n：节点数
s：存储字符的数组
g：邻接表表示的树
DFS遍历树，建立DFS序
为节点x分配DFS序号，更新对应层的线段树
1<<(s[x]-'a')：将字符转换为对应的位掩码
递归处理子节点
设置节点x的结束时间

构建树的邻接表（从2到n，每个节点的父节点）
读入字符序列，从根节点开始DFS
处理m个询问
每次询问节点x在深度h的子树中字符分布情况
查询对应线段树区间内的异或值
t^t&-t ? "No" : "Yes"：判断t是否是2的幂（即是否只有一种字符）
t&-t提取t的最低位1
如果t是2的幂，则t^t&-t为0（Yes）
否则为非0（No）

 */
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
constexpr int N = 5e5+5;

struct node { int l, r, v; } tr[N<<5];

int tot;
void update(int& o, int l, int r, int x, int v) {
    if (!o) o = ++tot;
    tr[o].v ^= v;
    if (l == r) return;
    if (mid >= x) update(tr[o].l, l, mid, x, v);
    else update(tr[o].r, mid+1, r, x, v);
}

int t;
void query(int o, int l, int r, int L, int R) {
    if (!o) return;
    if (L <= l && r <= R) return t ^= tr[o].v, void();
    if (mid >= L) query(tr[o].l, l, mid, L, R);
    if (mid < R) query(tr[o].r, mid+1, r, L, R);
}

int L[N], R[N], T[N], n;
char s[N];
vector<int> g[N];
void dfs(int x, int d) {
    L[x] = ++*L, update(T[d], 1, n, L[x], 1<<(s[x]-'a'));
    for (int y : g[x]) dfs(y, d + 1);
    R[x] = *L;
}

int m;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; ++i)
        scanf("%d", &t), g[t].push_back(i);
    scanf("%s", s + 1); dfs(1, 1);
    for (int i = 1, x, h; i <= m; ++i) {
        scanf("%d%d", &x, &h);
        t = 0, query(T[h], 1, n, L[x], R[x]);
        puts(t^t&-t ? "No" : "Yes");
    }
    return 0;
}