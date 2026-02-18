//
// Created by Psy.C on 2026/2/18.
//
/**
<: 向左移动
如果在最左列(y==1)，结果是{x, y-1}（出界）
如果左边是>，形成冲突{-1, -1}
否则递归搜索左边
>: 向右移动
如果在最右列(y==m)，结果是{x, y+1}（出界）
如果右边是<，形成冲突{-1, -1}
否则递归搜索右边
^: 向上移动
如果达到边界lim，结果是{x-1, y}（出界）
否则递归搜索上方

n: 网格高度
q: 查询次数
pos[N]: 每行属于哪个块
l[N], r[N]: 每个块的左右边界

预处理：O(nm√n)
修改：O(m√n)
查询：O(路径长度/√n)
空间复杂度：O(nm)
 */
#include <bits/stdc++.h>
#include <cmath>
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, M = 12;

ii dp[N][M];///记忆化搜索数组，存储从(x,y)出发的终点
char s[N][M];
int m;///网格宽度
ii dfs(int x, int y, const int lim) {//搜索的上界限制
    if (dp[x][y].first != 0 || dp[x][y].second != 0) return dp[x][y];
    ii res = {0, 0};
    if (s[x][y] == '<') {
        if (y == 1) res = {x, y-1};
        else if (s[x][y-1] == '>') res = {-1, -1};
        else res = dfs(x, y-1, lim);
    } else if (s[x][y] == '>') {
        if (y == m) res = {x, y+1};
        if (s[x][y+1] == '<') res = {-1, -1};
        else res = dfs(x, y+1, lim);
    } else if (s[x][y] == '^') {
        if (x == lim) res = {x-1, y};
        else res = dfs(x-1, y, lim);
    }
    return dp[x][y] = res;
}

int n, q, pos[N], l[N], r[N];
int main() {
    scanf("%d%d%d", &n, &m, &q);
    const int block = sqrt(n+0.5);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        pos[i] = (i-1)/block + 1;
    }
    int tot = n/block;
    if (n%block) tot++;
    for (int i = 1; i <= tot; ++i) {
        l[i] = (i-1)*block + 1;// 第i块的起始行号
        r[i] = i*block;//第i块的结束行号（理论值）
        if (i == tot) r[i] = min(r[i], n);//最后一块可能不满
        for (int j = l[i]; j <= r[i]; ++j)//遍历第i块内的每一行
            for (int k = 1; k <= m; ++k)
                dp[j][k] = dfs(j, k, l[i]);//不能越过第l[i]行
    }
    while (q--) {
        char op[2]; int x, y; scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'C') {
            char c[2]; scanf("%s", c); s[x][y] = c[0];//将位置(x,y)的字符改为新字符
            for (int i = l[pos[x]]; i <= r[pos[x]]; ++i)
                for (int j = 1; j <= m; ++j)
                    dp[i][j] = {0, 0};//将该位置的缓存结果清空
            for (int i = l[pos[x]]; i <= r[pos[x]]; ++i)
                for (int j = 1; j <= m; ++j)
                    dp[i][j] = dfs(i, j, l[pos[x]]);
        } else if (op[0] == 'A') {
            while (true) {
                if (x == -1 && y == -1) break;//遇到冲突
                if (x == 0 || y == 0 || x == n+1 || y == m+1) break;//出界
                const int tx = dp[x][y].first, ty = dp[x][y].second;
                x = tx, y = ty;// 更新当前位置为跳跃后的终点
            }
            printf("%d %d\n", x, y);
        }
    }
    return 0;
}