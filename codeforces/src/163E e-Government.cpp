//
// Created by Psy.C on 2025/11/27.
//
/*
*N = 1000050：最大节点数
n: 字符串数量
m: 查询操作数
id[N]: 存储每个字符串在AC自动机中的终点节点编号
inv[N]: 反向映射，节点编号到字符串编号
vis[N]: 标记字符串是否激活（1表示激活，0表示未激活）
s[N]: 临时存储字符串的字符数组
e[N]: AC自动机的fail树邻接表
 *
*定义AC自动机结构体
M = 26：小写字母数量
trie[N][M]: 字典树（Trie）
sz: 当前节点数
fa[N]: 父节点数组
fail[N]: fail指针数组
deg[N]: 入度数组（用于拓扑排序）
*插入字符串到字典树中
返回字符串终点节点的编号
*构建AC自动机的fail指针
同时构建fail树（用于后续DFS和树状数组操作）
 *
*DFS遍历fail树，为每个节点分配进入和离开时间戳
pos[u]: 节点u的进入时间
out[u]: 节点u的离开时间
tot: 时间戳计数器
 *
*树状数组的更新操作
在位置p添加值k
*树状数组的查询操作
查询前缀和[1,p]
 *
*读取n个字符串并插入AC自动机
建立双向映射关系
*构建AC自动机和fail树
DFS生成时间戳
*初始化：所有字符串都处于激活状态
使用树状数组的差分技巧标记区间
*处理m个操作
跳过空白字符读取操作符
*激活操作：激活第x个字符串
使用差分技巧更新树状数组
*去激活操作：去激活第x个字符串
使用差分技巧更新树状数组
*查询操作：在文本串中查找激活字符串的出现次数
遍历文本串在AC自动机中移动
查询每个节点的激活字符串数量
 *
*trie[k][i]：
从节点k通过字符('a'+i)转移到的子节点
fail[k]：
节点k的fail指针指向的节点
trie[fail[k]][i]：
从节点k的fail节点通过相同字符('a'+i)转移到的节点
整体含义：
节点trie[k][i]的fail指针指向trie[fail[k]][i]
 *
 *trie[0][i]
 *从根节点通过第i个字符（'a'+i）到达的子节点
 *
 *i & -i 的结果是保留i的二进制表示中最右边的1，其余位都置为0
 *实际上等于 2^(k-1)
 *
 *
*插入：O(∑|Si|) //所有字符串长度的总和
构建：O(∑|Si|)
操作：O(log N)（树状数组操作）
查询：O(|T| log N)（T为查询文本长度）
 *
 */
#include <iostream>
#include <queue>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+50;
int n, m, id[N], inv[N], vis[N];
char s[N];
vector<int> e[N];

struct AC {
#define M 26
    int trie[N][M], sz, fa[N];
    int fail[N], deg[N];
    int insert(const char *str) {
        int rt = 0;
        for (int i = 0; str[i] != 0; ++i) {
            const int nxt = str[i] - 'a';
            if (!trie[rt][nxt]) trie[rt][nxt] = ++sz;
            fa[trie[rt][nxt]] = rt;
            rt = trie[rt][nxt];
        }
        return rt;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < M; ++i) if (trie[0][i]) {
            fail[trie[0][i]] = 0, q.push(trie[0][i]);//第一层节点的fail指针都指向根节点
            e[0].push_back(trie[0][i]);
        }
        while (!q.empty()) {
            const int k = q.front(); q.pop();
            for (int i = 0; i < M; ++i) {
                if (trie[k][i]) {
                    fail[trie[k][i]] = trie[fail[k]][i];
                    e[trie[fail[k]][i]].push_back(trie[k][i]);
                    q.push(trie[k][i]);
                    deg[fail[trie[k][i]]]++;
                } else trie[k][i] = trie[fail[k]][i];
            }
        }
    }
} ac;

int pos[N], out[N], tot;
void dfs(const int u) {
    pos[u] = ++tot;
    for (const auto v : e[u]) dfs(v);
    out[u] = tot;
}

int pre[N];
void add(int p, const int k) {
    while (p <= tot) {
        pre[p] += k;
        p += p & -p;//跳转到父节点
    }
}

int query(int p) {
    int res = 0;
    while (p > 0) {
        res += pre[p];
        p -= p & -p;//跳转到前驱节点
    }
    return res;
}

int main() {
    fast;
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        id[i] = ac.insert(s);
        inv[id[i]] = i;
    }
    ac.build();
    dfs(0);
    for (int i = 1; i <= n; ++i) {
        add(pos[id[i]], 1);
        vis[i] = 1;
        add(out[id[i]] + 1, -1);
    }
    while (m--) {
        char t; cin.get(t);
        while (t == ' ' || t == '\n') cin.get(t);
        if (t == '+') {
            int x; cin >> x;
            if (vis[x] == 1) continue;
            vis[x] = 1;
            add(pos[id[x]], 1);
            add(out[id[x]] + 1, -1);
        } else if (t == '-') {
            int x; cin >> x;
            if (vis[x] == 0) continue;
            vis[x] = 0;
            add(out[id[x]] + 1, 1);
            add(pos[id[x]], -1);
        } else {
            cin >> s;
            int rt = 0, res = 0;
            for (int i = 0; s[i]; ++i) {
                const int nxt = s[i] - 'a';
                rt = ac.trie[rt][nxt];
                res += query(pos[rt]);
            }
            cout << res << '\n';
        }
    }
    return 0;
}