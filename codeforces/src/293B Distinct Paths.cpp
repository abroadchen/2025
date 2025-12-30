/**
* n, m, k：分别表示矩阵的行数、列数和颜色种类数
f[15][15]：记录每个位置的颜色状态
mask[1<<12]：位掩码数组，用于将位位置映射到颜色编号
c[15][15]：原始矩阵，记录每个位置的预设颜色（0表示未预设）
vis[15]：记录每种颜色的访问次数
 *
 *~zt 将已使用的位置设为 0，未使用的位置设为 1
 *zt = f[x][y-1] | f[x-1][y] 表示左边和上边已经使用的颜色状态
 *
*1<<k 表示 2^k，二进制为 1 后面跟 k 个 0
减 1 后变成 k 个连续的 1
 *
 *~zt & ((1<<k)-1) 获取未被相邻位置使用的颜色集合
* 1<<(t-1)
将数字 1 左移 (t-1) 位
结果是在第 t 位（从第1位开始计数）设置为 1，其余位为 0
* zt | (1<<(t-1))
按位或运算：将 zt 中的第 t 位置为 1
作用：标记颜色 t 已在当前位置使用
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mod 1000000007
using namespace std;

int n, m, k, f[15][15], mask[1<<12], c[15][15], vis[15];
int dfs(int x, int y) {
    if (y > m) x++, y = 1;//下一行第一列
    if (x > n) return 1;//找到一种有效方案
    int fr = -1, ret = 0;//fr用于记忆化
    const int zt = f[x][y - 1] | f[x - 1][y];//左边和上边位置的颜色状态并集
    for (int i = ~zt&(1<<k)-1; i; i -= i&(-i)) {
        const int t = mask[i & (-i)];//当前考虑的颜色
        if (c[x][y] == 0 || c[x][y] == t) {//位置未预设或预设颜色与当前颜色一致
            vis[t]++;//增加该颜色的使用次数
            f[x][y] = zt|1<<(t-1);//更新当前位置的颜色状态
            if (vis[t] == 1) {//第一次使用
                if (fr == -1) fr = dfs(x, y + 1);//计算结果并缓存 在同一行中向右移动
                ret += fr;//累加结果
            } else {
                ret += dfs(x, y + 1);//直接递归计算
            }
            ret %= mod;
            vis[t]--;//回溯，减少颜色使用次数
        }
    }
    return ret;
}


int main() {
    fast;
    cin >> n >> m >> k;
    if (n + m - 1 > k) { cout << "0"; return 0; }//最少路径数超过颜色数
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> c[i][j];
        vis[c[i][j]]++;//统计已使用颜色
    }
    int t = 1;
    for (int i = 1; i <= k; ++i) {//将位位置映射到颜色编号
        mask[t] = i;
        t *= 2;
    }
    cout << dfs(1, 1);
    return 0;
}