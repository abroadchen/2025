//
// Created by Psy.C on 2026/3/8.
//
/**
N=200000（节点数），M=500000（查询数），A=26（字母表大小）
ch[N+5][A+2]：Trie树的转移数组，ch[i][j]表示节点i通过字符j转移到的节点
cnt：节点计数器
ed[N+5]：记录第i个字符串在Trie树中的结尾节点

插入字符串s到Trie树中，id为其编号
逐字符遍历，建立Trie树路径
将字符串结尾节点记录到ed[id]中

构建AC自动机的失败函数（KMP思想）
BFS遍历所有节点，计算fail指针
fail[i]指向i节点的最长后缀匹配
链式前向星存储树结构
用于存储fail树（fail指针构成的树）
计算DFS序，用于将子树查询转化为区间查询
bfn[x]：节点x的进入时间
edt[x]：节点x的离开时间
树状数组（Binary Indexed Tree）
update：单点更新
query：前缀和查询（注意这里的写法是简化版）

q[N+5]：离线查询数组，按时间存储
ans[M+5]：存储查询结果
n, m：字符串数量和查询数量
s[N+5]：存储输入的字符串

读入n和m
读入n个字符串并插入Trie树
构建AC自动机的fail函数
构建fail树
计算DFS序
处理区间查询，使用差分思想
将[l,r]区间查询转化为[1,r] - [1,l-1]的查询
遍历每个字符串
对字符串的每个前缀在Trie树中更新
处理当前时间的查询，使用DFS序将子树查询转换为区间查询

创建BFS队列
将根节点（节点0）的所有直接子节点加入队列
这些节点的fail指针都指向根节点0（因为它们没有真后缀可以匹配）
使用BFS确保按层次遍历，保证处理节点x时，fail[x]已经计算完毕
遍历当前节点x的所有可能转移（26个字母）
情况1：节点x可以通过字符i转移到ch[x][i]
计算fail[ch[x][i]]：
ch[fail[x]][i]：从fail[x]节点通过字符i的转移
这个转移一定存在，因为fail[x]是x的最长真后缀匹配
数学原理：
假设当前路径为 root -> ... -> x --(字符i)--> ch[x][i]
fail[x] 表示从root到x的路径中，x的最长真后缀对应的节点
那么 ch[x][i] 的最长真后缀应该是 ch[fail[x]][i]（从fail[x]通过字符i转移）
情况2：节点x无法通过字符i转移
路径压缩：
将不存在的转移指向fail[x]通过字符i的转移
这样在匹配过程中，如果无法通过字符i转移，可以直接跳转到ch[fail[x]][i]
这是AC自动机的重要优化，避免了匹配失败时的回溯
 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5, M = 5e5, A = 26;

int ch[N+5][A+2], cnt, ed[N+5];
void insert(string s, int id) {
    int cur = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!ch[cur][s[i]-'a']) ch[cur][s[i]-'a'] = ++cnt;
        cur = ch[cur][s[i]-'a'];
    }
    ed[id] = cur;
}

int fail[N+5];
void get() {
    queue<int> q;
    for (int i = 0; i < A; ++i) if (ch[0][i]) q.push(ch[0][i]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < A; ++i) {
            if (ch[x][i]) {
                fail[ch[x][i]] = ch[fail[x]][i];
                q.push(ch[x][i]);
            } else ch[x][i] = ch[fail[x]][i];
        }
    }
}

int to[N+5], nxt[N+5], head[N+5], tot;
void add(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}

int bfn[N+5], edt[N+5], tim;
void dfs(int x) {
    bfn[x] = ++tim;
    for (int i = head[x]; i; i = nxt[i])
        dfs(to[i]);
    edt[x] = tim;
}
int t[N+5];
void update(int x ,int v) {
    for (int i = x; i <= cnt+1; i += i&-i) t[i] += v;
}
int query(int x) {
    int ret = 0;
    for (int i = x; i; i&=i-1) ret += t[i];
    return ret;
}

vector<pair<ii, int>> q[N+5];
int ans[M+5], n, m;
string s[N+5];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) cin >> s[i], insert(s[i], i);
    get();
    for (int i = 1; i <= cnt; ++i) add(fail[i], i);
    dfs(0);
    for (int i = 1, l, r, k; i <= m; ++i) {
        scanf("%d%d%d", &l, &r, &k);
        q[r].push_back({{i, 1}, k});
        q[l-1].push_back({{i, -1}, k});
    }
    for (int i = 1; i <= n; ++i) {
        int cur = 0;
        for (int j = 0; j < s[i].size(); ++j)
            cur = ch[cur][s[i][j]-'a'], update(bfn[cur], 1);
        for (auto it = q[i].begin(); it != q[i].end(); ++it) {
            int x = it->second, id = it->first.first, mul = it->first.second;
            ans[id] += mul*(query(edt[ed[x]]) - query(bfn[ed[x]] - 1));
        }
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}