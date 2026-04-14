//
// Created by Psy.C on 2026/4/14.
//
/**
cur: 当前连通块大小
vis[N][N]: 标记连通块ID
id: 当前连通块编号
s[N][N]: 输入网格
搜索连通块，统计大小
向四个方向扩展
给连通块编号
v[N*N]: 每个连通块在当前窗口中的出现次数
all: 当前窗口中所有连通块的总大小
mp[N*N]: 每个连通块的实际大小
push/pop: 添加/移除点，更新计数

sum[N][N]: 前缀和数组
k: 矩形大小
get(x,y): 计算k×k矩形内黑点数量


遍历所有点
对未访问的'.'进行DFS
记录每个连通块的大小
枚举矩形的起始行
初始化滑动窗口
添加初始窗口内的点
逐步移动窗口
移除离开窗口的点
添加进入窗口的点
更新最大值

枚举矩形的起始行（上边界）
i从1到n-k+1，确保k×k矩形不会越界
all = 0: 重置当前窗口内所有连通块的总大小
memset(v, 0, sizeof v): 清空连通块计数数组
j从i-1到i+k（共k+2行）
l从1到k（k列）
添加一个 (k+2) × k 的矩形区域内的所有'.'点
这个扩展区域包含了当前k×k矩形以及其周围一圈的点
j从i到i+k-1（k行）
添加第k+1列的k个点
补充 (k × 1) 的区域
与前面的区域结合，形成了围绕k×k矩形的完整边界
all: 当前窗口内所有连通块的总大小（包括k×k矩形内部和外部连通的）
k*k: k×k矩形的总面积
get(i+k-1, k): 计算从(i,1)到(i+k-1,k)这个k×k矩形内的'.'数量
all+k*k-get(...): 等于 all + 矩形内'.'的数量（因为k²包含了'.'和'#'，减去'#'的数量就剩下'.'的数量）
更新全局最优解

j从1到n-k，控制矩形的列移动
每次将k×k矩形向右移动一列
l从i到i+k-1（k行）
pop(l, j-1): 移除第j-1列的点（离开窗口）
push(l, j+k+1): 添加第j+k+1列的点（进入窗口）
这是核心的滑动窗口操作，移动k×1的竖直条
pop(i-1, j): 移除上方角落点
pop(i+k, j): 移除下方角落点
push(i-1, j+k): 添加新的上方角落点
push(i+k, j+k): 添加新的下方角落点
这些是滑动时四个角落的更新
计算当前窗口状态下的最优值
get(i+k-1, j+k): 获取当前k×k矩形内的'.'数量
更新全局最优解
时间复杂度：O(n²)，空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 505;

int cur, vis[N][N], id;
char s[N][N];
void dfs(int x, int y) {
    cur++; vis[x][y] = id;
    if (s[x-1][y] == '.' && !vis[x-1][y]) dfs(x-1, y);
    if (s[x+1][y] == '.' && !vis[x+1][y]) dfs(x+1, y);
    if (s[x][y-1] == '.' && !vis[x][y-1]) dfs(x, y-1);
    if (s[x][y+1] == '.' && !vis[x][y+1]) dfs(x, y+1);
}

int v[N*N], all, mp[N*N];
void push(int x, int y) {
    if (!vis[x][y]) return;
    if (!v[vis[x][y]]) all += mp[vis[x][y]];
    v[vis[x][y]]++;
}
void pop(int x, int y) {
    if (!vis[x][y]) return;
    v[vis[x][y]]--;
    if (!v[vis[x][y]]) all -= mp[vis[x][y]];
}

int sum[N][N], k;
int get(int x, int y) {
    return sum[x][y] - sum[x-k][y] - sum[x][y-k] + sum[x-k][y-k];
}

int n;
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
            if (s[i][j] == '.') sum[i][j]++;
        }
    id = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '.' && !vis[i][j]) {
                cur = 0;
                dfs(i, j);
                mp[id++] = cur;
            }
        }
    int ans = 0;
    for (int i = 1; i <= n-k+1; i++) {
        all = 0;
        memset(v, 0, sizeof v);
        for (int j = i-1; j <= i+k; j++)
            for (int l = 1; l <= k; l++) push(j, l);
        for (int j = i; j < i+k; j++) push(j, k+1);
        ans = max(ans, all+k*k-get(i+k-1, k));
        for (int j = 1; j <= n-k; j++) {
            for (int l = i; l < i+k; l++) {
                pop(l, j-1);
                push(l, j+k+1);
            }
            pop(i-1, j); pop(i+k, j);
            push(i-1, j+k); push(i+k, j+k);
            ans = max(ans, all+k*k-get(i+k-1, j+k));
        }
    }
    printf("%d\n", ans);
    return 0;
}