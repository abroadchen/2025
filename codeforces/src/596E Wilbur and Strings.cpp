//
// Created by Psy.C on 2026/3/20.
//
/**
rd[N*N]：入度数组
st：Tarjan算法使用的栈
flag[N*N]：节点是否在栈中的标记
use[N*N][15]：记录每个强连通分量包含的数字
dfn[N*N], low[N*N]：Tarjan算法的发现时间和低链接值
sz[N*N]：每个节点对应的数字值
dfs(id)：Tarjan算法的核心函数，找强连通分量
初始化所有数组
对每个未访问的节点运行DFS
dfs2(id, x)：在图中搜索字符串
x == -1：字符串完全匹配，返回true
遍历所有邻接节点，检查是否能匹配字符串的当前字符

读取网格和查询数量
将字符网格转换为数字网格
读取移动规则
根据每个位置的数字和移动规则构建图
运行Tarjan算法
对每个查询，从入度为0的节点开始搜索
如果能在图中找到匹配的路径，输出"YES"，否则输出"NO"

一旦 tag 变为 true，后续的 dfs2 调用就不会被执行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 205;

struct node { int to, nxt; } e[N*N];

int rd[N*N], cnt, head[N*N];
void add(int st, int to) {
    rd[to]++;
    e[cnt] = {to, head[st]}, head[st] = cnt++;
}
void init() {
    memset(rd, 0, sizeof(rd));
    memset(head, -1, sizeof(head));
    cnt = 0;
}

int n, m;
bool ok(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }
int get(int x, int y) { return (x-1)*m + y; }

stack<int> st;
bool flag[N*N], vis[N*N], use[N*N][15];
int dfn[N*N], low[N*N], tim, sz[N*N];
void dfs(int id) {
    st.push(id); flag[id] = true;
    dfn[id] = low[id] = ++tim;
    for (int i = head[id]; i+1; i = e[i].nxt) {
        int w = e[i].to;
        if (dfn[w] == -1) { dfs(w); low[id] = min(low[id], low[w]); }
        else if (flag[w]) low[id] = min(low[id], dfn[w]);
    }
    if (dfn[id] == low[id]) {
        while (true) {
            int x = st.top();
            if (x != id) { vis[x] = false; rd[id] = 0; }
            st.pop();
            flag[x] = false;
            use[id][sz[x]] = true;
            if (x == id) break;
        }
    }
}

void tarjan() {
    memset(dfn, -1, sizeof(dfn));
    memset(flag, false, sizeof(flag));
    memset(use, false, sizeof(use));
    memset(vis, true, sizeof(vis));
    tim = 0;
    for (int i = 1; i <= n*m; ++i)
        if (dfn[i] == -1) dfs(i);
}

char s[N*10000];
bool dfs2(int id, int x) {
    if (x == -1) return true;
    bool tag = false;
    for (int i = head[id]; i + 1; i = e[i].nxt) {
        int w = e[i].to;
        if (!vis[w]) continue;
        if (use[w][s[x] - '0']) tag = tag || dfs2(w, x-1);
        else tag = tag || dfs2(w, x);
    }
    return tag;
}

int q, t[N][N], a[N], b[N];
char stu[N][N];
int main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> stu[i];
        for (int j = 0; j < m; ++j) {
            t[i][j+1] = stu[i][j] - '0';
            sz[get(i, j+1)] = t[i][j+1];
        }
    }
    for (int i = 0; i <= 9; ++i) cin >> a[i] >> b[i];
    init();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (ok(i+a[t[i][j]], j+b[t[i][j]]))
                add(get(i+a[t[i][j]], j+b[t[i][j]]), get(i, j));
    tarjan();
    while (q--) {
        cin >> s; int len = strlen(s), i;
        for (i = 1; i <= n*m; ++i) {
            if (rd[i] == 0) {
                int x = len;
                while (x >= 1) {
                    if (use[i][s[x-1] - '0']) x--;
                    else break;
                }
                if (x == 0) { cout << "YES\n"; break; }
                if (dfs2(i, x-1)) { cout << "YES\n"; break; }
            }
        }
        if (i > n*m) cout << "NO\n";
    }
    return 0;
}