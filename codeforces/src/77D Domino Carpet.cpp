//
// Created by Psy.C on 2025/11/5.
//
/*
*定义长整型别名和常量：
N = 255: 最大行列数
MOD = 1e9+7: 模数，防止结果过大
变量说明：
n, m: 行数和列数
t[N][N]: 状态转换表
dp[N]: 主要的动态规划数组
f[N][2]: 辅助DP数组
s[3][N*5]: 字符串数组，用于读取输入
 *
*统计3行中从r到c列的'O'字符总数
根据'O'的数量返回不同状态：
x=2或3: 如果右上角是'O'返回1，否则返回0
x=6: 如果左中是'O'返回1，否则返回0
其他情况返回2
 *
*读取3行字符串表示图案
将每4列作为一个单位，调用g()函数判断状态
存储在t[i][j]中
每行之间可能还有分隔符
 *
*初始化dp[0] = 1（空方案数为1）

对于每一列j：

如果行数n是偶数：
检查第j列所有行的状态是否都不是0
如果是，则dp[j] += dp[j-1]
*当j>1时，使用二维DP：

f[i][0]和f[i][1]表示处理到第i行的两种状态
根据相邻两列的状态转移规则更新f数组
最后通过dp[j-2] * f[n][1]更新dp[j]
 *
*模式识别: 通过函数g()识别特定的图案模式
状态压缩: 将复杂的图案转换为简单的状态码(0,1,2)
动态规划:
dp[j]表示处理前j列的方案数
f[i][0/1]表示处理到第i行的中间状态
转移方程: 根据相邻列的状态关系进行状态转移
 *
 *
 *时间复杂度为O(n×m)，空间复杂度为O(n×m)
 */
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 255, MOD = 1e9+7;

int n, m, t[N][N], dp[N], f[N][2];
char s[3][N*5];

int g(int r, int c) {
    int x = 0;
    for (int i = 0; i < 3; ++i) for (int j = r; j <= c; ++j) {
        if (s[i][j] == 'O') x++;
    }
    if (x == 2 || x == 3) {
        if (s[0][c] == 'O') return 1;
        return 0;
    }
    if (x == 6) {
        if (s[1][r] == 'O') return 1;
        return 0;
    }
    return 2;
}


int main() {
    scanf("%d%d",&n,&m); scanf("%s",s[0]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) scanf("%s",s[j]);
        int l = 1, r = 3;
        for (int j = 1; j <= m; ++j) {
            t[i][j] = g(l, r);
            l += 4; r += 4;
        }
        scanf("%s",s[0]);
    }
    dp[0] = 1;
    for (int j = 1; j <= m; ++j) {
        if (n % 2 == 0) {
            int flag = 1;
            for (int i = 1; i <= n; ++i) {
                if (t[i][j] == 0) {
                    flag = 0;
                    break;
                }
            }
            if (flag) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
        if (j > 1) {
            f[0][0] = 1, f[0][1] = 0;
            for (int i = 1; i <= n; ++i) {
                f[i][0] = f[i][1] = 0;
                if (t[i][j-1]!=1&&t[i][j]!=1) f[i][1] = (f[i-1][0]+f[i-1][1]) % MOD;
                if (i == 1) continue;
                if (t[i-1][j-1]&&t[i-1][j]&&t[i][j-1]&&t[i][j]) {
                    f[i][1] = (f[i][1]+f[i-2][1]) % MOD;
                    f[i][0] = (f[i][0]+f[i-2][0]) % MOD;
                }
            }
            dp[j] = (dp[j]+(ll)dp[j-2]*f[n][1]%MOD) % MOD;
        }
    }
    printf("%d\n",dp[m]);
    return 0;
}