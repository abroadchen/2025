//
// Created by Psy.C on 2025/11/30.
//
/*
*N = 4010：字符串相关数组大小
M = 1e6：Trie树节点数上限
n：字符串数量
m：需要选择的字符串数量
s[N]：临时存储输入字符串的缓冲区
*ch[M][27]：Trie树的孩子节点指针（26个字母 + 1个额外空间）
tot：Trie树节点计数器，初始为1（根节点）
siz[M]：每个节点的子节点数量
ed[M]：标记以该节点结尾的字符串数量
 *
*Trie树插入操作：
计算字符串长度
从根节点（编号1）开始
逐字符遍历字符串：
计算字符相对于'a'的偏移量
如果该字符对应的子节点不存在，创建新节点
移动到子节点
在终点节点标记字符串结束（ed[x]++）
 *
*dep[M]：节点深度数组
cnt：重构树节点计数器
num[N]：每个重构节点包含的字符串数量
g[N]：重构后的树的邻接表
 *
*DFS重构Trie树为简化树：
只在以下情况创建新节点：
根节点（x == 1）
分支节点（siz[x] > 1，有多个子节点）
叶节点且标记字符串结束（ed[x] > 0）
dep[++cnt] = d：记录新节点深度
g[lst].push_back(cnt)：建立父子关系
lst = cnt：更新当前链的末端
num[cnt] = ed[x]：记录该节点包含的字符串数
 *
 *dp[x][j]：在节点x的子树中选择j个字符串能得到的最大价值
*树形DP过程：
初始化：dp[x][0] = 0
遍历所有子节点：
递归处理子树
累加子树中的字符串数量
背包合并：将子树的选择方案合并到当前节点
dp[x][j] = max(dp[x][j], dp[x][j-k] + dp[y][k])
添加当前层贡献：
(dep[x] - dep[fa])：当前层的深度差
i * (i - 1) / 2：选择i个字符串时的内部配对数
这部分计算的是在同一前缀下选择多个字符串的额外代价
 *
*读入参数n（字符串数）和m（要选择的字符串数）
读入并插入所有字符串到Trie树
DFS重构Trie树为简化树结构
执行树形DP计算最优解
输出在根节点选择m个字符串的最大价值
 *
*Trie构建：O(∑|si|)
树形DP：O(节点数 × m²)
总体：O(n × maxlen + m³)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 4010, M = 1e6;
int n, m;
char s[N];

int ch[M][27], tot = 1, siz[M], ed[M];
inline void insert(char t[]) {
    const int len = static_cast<int>(strlen(t));
    int x = 1;
    for (int i = 0; i < len; ++i) {
        const int c = s[i] - 'a';
        if (!ch[x][c]) ch[x][c] = ++tot, siz[x]++;
        x = ch[x][c];
    }
    ed[x]++;
}

int dep[M], cnt, num[N];
vector<int> g[N];
inline void dfs(const int x, const int d, int lst) {
    if (x == 1 || siz[x] > 1 || ed[x])
        dep[++cnt] = d, g[lst].push_back(cnt), lst = cnt, num[cnt] = ed[x];
    for (int i = 0; i < 26; ++i) if (ch[x][i]) {
        dfs(ch[x][i], d + 1, lst);
    }
}

int dp[N][N];
inline void f(const int x, const int fa) {
    dp[x][0] = 0;
    for (const auto y : g[x]) {
        f(y, x), num[x] += num[y];
        for (int j = min(num[x], m); j; --j)//总共选择j个字符串
            for (int k = min(num[y], j); k; --k)//从当前子树y中选择k个
                dp[x][j] = max(dp[x][j], dp[x][j-k] + dp[y][k]);
    }
    for (int i = 1; i <= num[x]; ++i)
        dp[x][i] += (dep[x] - dep[fa]) * (i * (i - 1) / 2);
}

int main() {
    fast;
    cin>>n>>m;
    for (int i = 1; i <= n; ++i) { cin>>s; insert(s); }
    dfs(1, 0, 0), f(1, 0);
    cout << dp[1][m] << '\n';
    return 0;
}