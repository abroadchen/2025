//
// Created by Psy.C on 2026/1/12.
//
/**
*
n：网格列数
g[N][3]：网格状态（0可放，1不可放）3表示3行
dp[M][1<<3]：动态规划数组，1<<3=8表示每列3行的状态 每列有8种状态（3行的2^3种组合）
*x：当前列的障碍物状态（用二进制表示）
j：当前列放置多米诺的状态
j & x：检查放置状态与障碍物是否有冲突
状态转移考虑不同放置方式的组合
*从'O'位置向四个方向（上下左右）尝试放置2格多米诺
检查是否在边界内且路径无障碍
*枚举所有可能的放置组合
使用容斥原理计算：奇数个放置的加，偶数个放置的减
__builtin_popcount(i)：计算i的二进制中1的个数
 *
*读入3×n网格
'.' 表示可放置
'X' 表示障碍
'O' 表示特殊位置（必须被覆盖）
 *
*g[i][0]对应最低位
g[i][1]<<1左移1位
g[i][2]<<2左移2位
*状态转移：当前状态j|x的方案数等于上一列互补状态的方案数
7-j：计算与状态j互补的状态
*当j为3(011)或6(110)时，添加额外的转移
这对应特定的多米诺放置模式
*当j为7(111)时，添加更多转移
dp[i][j|x] += dp[i-1][6]和dp[i][j|x] += dp[i-1][3]
% mod：取模运算防止溢出
 *返回第n列全满状态的方案数
 *
*双重循环处理网格
.：可放置，g2[i+1][j] = 0
X：障碍，g2[i+1][j] = 1
O：特殊点，g2[i+1][j] = 1，记录坐标x=i+1, y=j
 *
 *
* 位0（最低位）：第1行（row 1）
位1：第2行（row 2）
位2（最高位）：第3行（row 3）
*j = 1 (001)：仅第1行被占用（可能是一个垂直多米诺的上半部分）
j = 2 (010)：仅第2行被占用
j = 3 (011)：第1行和第2行都被占用（垂直多米诺占据这两行）
j = 6 (110)：第2行和第3行都被占用（垂直多米诺占据这两行）
j = 7 (111)：3行都被占用
 *
*dx[]：x方向（行）的偏移量数组
dx[0] = 1：向下
dx[1] = -1：向上
dx[2] = 0：不动（水平方向）
dx[3] = 0：不动（水平方向）
dy[]：y方向（列）的偏移量数组
dy[0] = 0：不动（垂直方向）
dy[1] = 0：不动（垂直方向）
dy[2] = 1：向右
dy[3] = -1：向左
*i 的含义
i：方向索引（0,1,2,3），表示四个方向之一
j 的含义
j：步数索引（1,2），表示从起点走几步
计算过程
当 i = 0（向下方向）：
x + dx[0] * j = x + 1 * j = x + j
y + dy[0] * j = y + 0 * j = y
从点 (x,y) 向下移动 j 步
当 i = 1（向上方向）：
x + dx[1] * j = x + (-1) * j = x - j
y + dy[1] * j = y + 0 * j = y
从点 (x,y) 向上移动 j 步
当 i = 2（向右方向）：
x + dx[2] * j = x + 0 * j = x
y + dy[2] * j = y + 1 * j = y + j
从点 (x,y) 向右移动 j 步
当 i = 3（向左方向）：
x + dx[3] * j = x + 0 * j = x
y + dy[3] * j = y + (-1) * j = y - j
从点 (x,y) 向左移动 j 步
 *
 */
#include <iostream>
#include <cstring>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10100
#define M 11000
#define mod 1000000007
using namespace std;

int n, g[N][3];
ll dp[M][1<<3];
ll get() {
    memset(dp, 0, sizeof(dp)); dp[0][7] = 1;//所有位置都可用
    for (int i = 1; i <= n; ++i) {
        const int x = g[i][0] + (g[i][1]<<1) + (g[i][2]<<2);//将当前列的障碍物状态编码为一个数字
        for (int j = 0; j < 1<<3; ++j) {
            if (j & x) continue;
            dp[i][j|x] = dp[i-1][7-j];
            if (j == 3 || j == 6)
                dp[i][j|x] = (dp[i][j|x] + dp[i-1][7]) % mod;
            if (j == 7) {
                dp[i][j|x] = (dp[i][j|x] + dp[i-1][6]) % mod;
                dp[i][j|x] = (dp[i][j|x] + dp[i-1][3]) % mod;
            }
        }
    }
    return dp[n][7];
}

int x, y, g2[N][3];
ll solve() {
    vector<int> a;//可行方向的向量
    constexpr int dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1};//下、上、右、左
    for (int i = 0; i < 4; ++i) {
        bool ok = true;
        if (x + dx[i] * 2 > 0 && x + dx[i] * 2 <= n &&
            y + dy[i] * 2 >= 0 && y + dy[i] * 2 < 3) {//2步后的位置是否在边界内
            for (int j = 1; j <= 2; ++j) if (g2[x+dx[i]*j][y+dy[i]*j]) ok = false;//路径是否无障碍
        } else ok = false;
        if (ok) a.push_back(i);//将可行方向加入向量
    }
    ll res = 0;
    for (int i = 1; i < 1<<a.size(); ++i) {//枚举所有可能的方向组合
        memcpy(g, g2, sizeof g2);//复制原始状态到工作数组
        for (int j = 0; j < a.size(); ++j) if (1&(i>>j)) {//第j位是否为1（是否选择该方向）
            for (int k = 1; k <= 2; ++k) g[x+dx[a[j]]*k][y+dy[a[j]]*k] = 1;//路径标记为障碍（已放置多米诺）
        }
        if (__builtin_popcount(i)&1) res = (res + get()) % mod; else {
            res = (res - get() + mod) % mod;
        }
    }
    return res % mod;
}


int main() {
    fast;
    cin >> n; char s[3][M];//输入的网格
    for (auto& i : s) cin >> i;//读入每行
    for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) {
        if (s[j][i] == '.') g2[i+1][j] = 0;
        else if (s[j][i] == 'X') g2[i+1][j] = 1;
        else if (s[j][i] == 'O') {
            g2[i+1][j] = 1;
            x = i + 1;
            y = j;
        }
    }
    cout << solve() << '\n';
    return 0;
}