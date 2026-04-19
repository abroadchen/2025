//
// Created by Psy.C on 2026/4/18.
//
/**
S = 1e7+5: 线段树节点总数上限
node: 线段树节点结构，包含左右子节点指针
t[S]: 线段树节点数组
cnt: 已使用节点计数
在动态开点线段树中插入位置x
p = ++cnt: 动态创建新节点
递归插入到对应叶子节点
合并两棵线段树
p^q：如果其中一个为空，返回另一个
递归合并左右子树
查询区间[s,e]是否有点存在
s <= l && r <= e: 完全覆盖区间时返回true
分别在左右子树中查询

n: 字符串长度
ans: 最终答案
S = N<<1: SAM节点数上限（约2*N）
node: SAM节点结构
tr[26]: 转移数组（26个小写字母）
lk: 后缀链接
mx: 该节点代表的最长字符串长度
构建邻接表，用于遍历parent tree
head[u]: 节点u的邻接链表头
add: 添加边u→v
cnt: SAM节点计数
lst: 上一个添加的节点
rt[S]: 每个SAM节点对应的线段树根
pos[S]: 记录节点在原字符串中的结束位置
这是SAM的扩展函数，每次添加一个字符c到位置id
根据后缀链接构建parent tree的邻接表
自底向上合并子节点的线段树
将子节点v的信息合并到父节点u中
f[u]: 以节点u结尾的最长匹配序列长度
g[u]: 以节点u结尾的最优匹配序列的起始节点
如果节点u的后缀链接指向根节点，f[u] = 1
否则检查是否存在合适的重叠匹配
sgt::query: 检查是否能在合适区间找到匹配位置
更新全局答案ans


p = lst: p是上一个节点（上一个字符串的终点状态）
np = lst = ++cnt: 创建新节点np，同时更新lst为当前新节点
sgt::insert(rt[np], 1, n, id): 在节点np对应的线段树中插入位置id
pos[np] = id: 记录该节点在原字符串中的结束位置
t[np].mx = t[p].mx + 1: 新节点的最长字符串长度比父节点多1
第一阶段：沿着后缀链接添加转移
从节点p开始，沿着后缀链接向上走
对于所有没有字符c转移的节点，添加c→np的转移
这是因为字符串s[p]+c现在也出现在位置id，应该指向np
第二阶段：处理后缀链接
如果p变为0（到达根节点），说明字符串c是全新的
新节点np的后缀链接指向根节点1
情况1：不需要分裂
q = t[p].tr[c]: q是p通过字符c能到达的节点
如果t[q].mx == t[p].mx + 1，说明q节点刚好表示字符串s[p]+c
直接让np的后缀链接指向q
情况2：需要创建分裂节点
创建新节点nq作为q的副本，但mx值改为t[p].mx + 1
t[nq] = t[q]: 复制q的转移函数
t[nq].mx = t[p].mx + 1: 调整最大长度
pos[nq] = pos[q]: 复制位置信息
t[np].lk = t[q].lk = nq: 更新后缀链接
更新旧路径
将所有原来指向q的转移改为指向nq
这些转移应该指向较短的那个版本（长度为t[p].mx + 1）


根节点特殊情况
如果节点u的后缀链接指向根节点1（说明u是最顶层的非根节点）
这意味着我们找到了一个新的匹配起点
f[u] = 1: 匹配序列长度为1
g[u] = u: 起始状态就是u本身
非根节点处理
pa = t[u].lk: 获取u的父节点（通过后缀链接）
这里处理的是除了根节点以外的其他节点
g[pa]: 父节点pa对应的起始状态
rt[g[pa]]: 起始状态g[pa]对应的线段树根
查询区间：[pos[u]-t[u].mx+t[g[pa]].mx, pos[u]-1]
pos[u]: 当前节点u在原字符串中的结束位置
t[u].mx: 当前节点代表的最长字符串长度
t[g[pa]].mx: 起始状态g[pa]代表的最长字符串长度
这个区间表示在u的字符串中，能够与g[pa]匹配的重叠区域
如果查询返回true，说明存在合适的重叠匹配
f[u] = f[pa] + 1: 匹配序列长度加1
g[u] = u: 更新起始状态为当前状态u
如果无法找到合适的重叠匹配
f[u] = f[pa]: 继承父节点的匹配序列长度
g[u] = g[pa]: 继承父节点的起始状态
更新全局最大匹配序列长度
遍历parent tree中的所有子节点
递归处理每个子节点

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5;

namespace sgt {
    constexpr int S = 1e7+5;
    struct node { int lc, rc; } t[S];
    int cnt;
    void insert(int &p, int l, int r, int x) {
        p = ++cnt;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid) insert(t[p].lc, l, mid, x);
        else insert(t[p].rc, mid+1, r, x);
    }
    int merge(int p, int q) {
        if (!p || !q) return p^q;
        int x = ++cnt;
        t[x].lc = merge(t[p].lc, t[q].lc);
        t[x].rc = merge(t[p].rc, t[q].rc);
        return x;
    }
    bool query(int p, int l, int r, int s, int e) {
        if (!p) return false;
        if (s <= l && r <= e) return true;
        int mid = (l + r) >> 1;
        if (s <= mid && query(t[p].lc, l, mid, s, e)) return true;
        if (mid < e && query(t[p].rc, mid+1, r, s, e)) return true;
        return false;
    }
}

int n, ans;
namespace sam {
    constexpr int S = N<<1;
    struct node { int tr[26], lk, mx; } t[S];
    int ver[S], nxt[S], head[S], tot;
    void add(int u, int v) {
        ver[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    }
    int cnt = 1, lst = 1, rt[S], pos[S];
    void ex(int id, int c) {
        int p = lst, np = lst = ++cnt;
        sgt::insert(rt[np], 1, n, id);
        pos[np] = id;
        t[np].mx = t[p].mx + 1;
        for (; p && t[p].tr[c] == 0; p = t[p].lk) t[p].tr[c] = np;
        if (!p) t[np].lk = 1;
        else {
            int q = t[p].tr[c];
            if (t[q].mx == t[p].mx + 1) t[np].lk = q;
            else {
                int nq = ++cnt;
                t[nq] = t[q], t[nq].mx = t[p].mx + 1, pos[nq] = pos[q], t[np].lk = t[q].lk = nq;
                for (; p && t[p].tr[c] == q; p = t[p].lk) t[p].tr[c] = nq;
            }
        }
    }
    void build() {
        for (int i = 2; i <= cnt; i++) add(t[i].lk, i);
    }
    void dfs(int u) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ver[i];
            dfs(v);
            rt[u] = sgt::merge(rt[u], rt[v]);
        }
    }
    int f[S], g[S];
    void dp(int u) {
        if (t[u].lk == 1) f[u] = 1, g[u] = u;
        else if (u > 1) {
            int pa = t[u].lk;
            if (sgt::query(rt[g[pa]], 1, n, pos[u]-t[u].mx+t[g[pa]].mx, pos[u]-1))
                f[u] = f[pa] + 1, g[u] = u;
            else f[u] = f[pa], g[u] = g[pa];
        }
        ans = max(ans, f[u]);
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ver[i];
            dp(v);
        }
    }
}

char str[N];
int main() {
    scanf("%d", &n); scanf("%s", str+1);
    for (int i = 1; i <= n; ++i) sam::ex(i, str[i]-'a');
    sam::build(); sam::dfs(1); sam::dp(1);
    printf("%d\n", ans);
    return 0;
}