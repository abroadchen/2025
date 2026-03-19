//
// Created by Psy.C on 2026/3/18.
//
/**
lk[N][N]：邻接矩阵，记录节点间的连接关系
add 函数：将节点u和v标记为相连
nxt[M][2]：AC自动机转移数组，每个状态对'a'和'b'字符的转移
fail[M]：失败指针数组
b[M]：记录以某个状态结尾的模式串编号
tot：当前使用的最大节点编号
在AC自动机中插入字符串s，长度为l，标识为id
遍历字符串每个字符，构建Trie树
将字符串结尾状态标记为该字符串的ID
查找当前状态p的最近结束节点
如果当前状态是根节点返回-1
如果当前状态有结束标记直接返回
使用记忆化递归查找失败指针链上的结束节点
BFS构建失败指针
第一个while循环：构建fail指针并更新转移表
第二个while循环：预计算up数组，用于快速找到匹配的模式串
在文本串s中查找所有模式串的匹配
对于每个位置，检查是否匹配到其他模式串
避免自己匹配自己的情况（b[t] == id）
执行Floyd-Warshall算法，计算传递闭包
更新可达性矩阵，判断是否存在间接匹配
e：二分图边的邻接表
vl, vr：左右部分节点访问标记
mat：匹配数组
从右侧节点开始DFS，标记可达节点
增广路径搜索，实现匈牙利算法
寻找最大匹配

初始结果为n，减去匹配数量得到最小顶点覆盖

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 755, M = 1e7+5;

bool lk[N][N];
void add(int u, int v) { lk[u][v] = 1; }

namespace ac {
    int nxt[M][2], fail[M], b[M], tot;
    void insert(const char *s, int l, int id) {
        int p = 0;//当前状态，初始为根节点0
        for (int i = 0; i < l; ++i) {//遍历字符串s的每个字符
            int c = s[i] - 'a';//将字符转换为索引
            if (!nxt[p][c]) nxt[p][c] = ++tot;//如果不存在转移边，创建新节点
            p = nxt[p][c];//移动到下一个状态
        }
        b[p] = id;//在结束状态标记该模式串的ID
    }
    int up[M];
    int find(int p) {
        if (p == 0) return -1;//到达根节点，没有匹配的模式串
        if (b[p]) return p;//当前状态已经有模式串结束，直接返回
        if (up[p]) return up[p];//已经计算过，直接返回缓存结果
        return up[p] = find(fail[p]);//递归查找失败指针，并缓存结果
    }
    int l, r, q[M];
    bool vis[M];
    void get() {
        l = 1;//初始化队列
        for (int i = 0; i < 2; ++i)//对根节点的两个子节点
            if (nxt[0][i]) q[++r] = nxt[0][i];
        while (l <= r) {
            int p = q[l++];//取出队首元素
            for (int c = 0; c < 2; ++c) {//对每个字符
                int v = nxt[p][c];//子节点
                if (!v) nxt[p][c] = nxt[fail[p]][c];//虚拟转移
                else fail[v] = nxt[fail[p]][c], q[++r] = v;//设置失败指针
            }
        }
        q[l=r=1] = 0; vis[0] = 1;//重新初始化BFS
        while (l <= r) {
            int p = q[l++]; up[p] = find(fail[p]);
            for (int c = 0; c < 2; ++c) if (!vis[nxt[p][c]]) {
                int v = nxt[p][c];
                vis[v] = 1; q[++r] = v;
            }
        }
    }
    void get(const char *s, int len, int id) {
        int p = 0;//从根节点开始
        for (int i = 0; i < len; ++i) {//遍历文本串
            int c = s[i] - 'a';//获取字符索引
            p = nxt[p][c];//在AC自动机中转移
            int t = b[p] ? p : up[p];//如果当前状态有结束，用当前；否则用up数组
            while (t != -1 && b[t] == id) t = up[t];//避免自己匹配自己
            if (t != -1) add(id, b[t]);//添加匹配关系
        }
    }
}

int n;
void floyd() {
    for (int k = 1; k <= n; ++k)//中间节点
        for (int i = 1; i <= n; ++i) if (k != i)//起始节点
            for (int j = 1; j <= n; ++j) if (j != i && j != k)//结束节点
                lk[i][j] |= lk[i][k]&lk[k][j];
}

vector<int> e[N<<1];
int vl[N<<1], vr[N<<1], mat[N<<1];
void fd(int u) {
    if (vr[u]) return;//如果已访问过，直接返回
    vr[u] = 1;
    for (int &v : e[u]) if (v != mat[u]) {//遍历相邻节点
        if (!vl[v])//如果左侧节点未被访问
            vl[v] = 1, fd(mat[v]);//标记并递归访问其匹配节点
    }
}

int vis[N<<1];
bool dfs(int u) {
    if (vis[u]) return 0;
    vis[u] = 1;
    for (int v : e[u]) if (!mat[v] || dfs(mat[v])) {
        mat[v] = u, mat[u] = v;//建立新的匹配关系
        return 1;//找到增广路径
    }
    return 0;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
inline void rds(vector<char>& s) {
    char ch = getchar();
    while (isspace(ch)) ch = getchar();
    while (!isspace(ch) && ch != EOF)
        s.push_back(ch), ch = getchar();
}

vector<char> str[N];
int main() {
    fast;
    n = rd();
    for (int i = 1; i <= n; ++i) {
        rds(str[i]);
        ac::insert(&str[i][0], str[i].size(), i);
    }
    ac::get();
    for (int i = 1; i <= n; ++i)
        ac::get(&str[i][0], str[i].size(), i);//在每个字符串中查找匹配
    floyd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) if (i != j && lk[i][j])
            e[i].push_back(j+n), e[j+n].push_back(i);//构建二分图
    int res = n;
    for (int i = 1; i <= n; ++i)
        if (!mat[i]) {
            memset(vis, 0, sizeof(vis));
            res -= dfs(i);//寻找最大匹配
        }
    cout << res << '\n';
    for (int i = 1; i <= n; ++i)
        if (!mat[i+n]) fd(i+n);//标记未匹配节点可达区域
    for (int i = 1; i <= n; ++i)
        if (!vl[i] && vr[i+n]) cout << i << ' ';
    return 0;
}