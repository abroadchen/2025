//
// Created by Psy.C on 2026/2/10.
//
/**
st[N]: 存储每个数字对应的质因数状态，使用位掩码表示
dp[i][j]表示处理到第i个数且质因数状态为j时的最小代价

对每个质数f，将所有f的倍数j标记上质数f的信息
st[j] |= 1<<i: 将j对应的状态中第i位置1，表示j包含质因子pri[i]
m = (1<<16)-1: 所有可能质因数状态的最大值（全1）
path[N][M]: 记录路径数组，用于回溯构造答案
b[N]: 输出结果数组

外层循环：遍历每个输入的数字（从1到n）
中层循环：遍历当前所有可能的质因数状态
内层循环：尝试所有可能的替换值k（1到59）
if((st[k]&j) == 0): 检查新值k的质因数与当前状态j是否有冲突，确保无公共质因数
const int to = j | st[k]: 计算新的状态，k的质因数加入后的新状态
如果找到更优解，则更新dp值并记录路径

寻找最终状态下代价最小的状态s
mn: 记录最小总代价
从最后一步开始向前回溯
b[i] = path[i][s]: 获取第i步选择的数值
s -= st[path[i][s]]: 更新状态，移除当前选择数字对应的质因数
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 107
#define M 1<<16//65536，即状态数的最大值
#define inf 0x3f3f3f3f//1061109567
using namespace std;

int pri[] = {//前16个质数的数组
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53
}, st[N], dp[N][M];

void init() {
    for (int i = 0; i < 16; ++i) {
        const int f = pri[i];
        for (int j = f; j < 60; j += f) st[j] |= 1<<i;
    }
    memset(dp, 0x3f, sizeof(dp));
}

int n, a[N], m = (1<<16)-1, path[N][M], b[N];
void out() {
    cin >> n; init();
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) for (int j = 0; j <= m; ++j)
        for (int k = 1; k < 60; ++k) if ((st[k]&j) == 0) {
            if (const int to = j | st[k]; dp[i][to] > dp[i-1][j] + abs(a[i] - k)) {
                dp[i][to] = dp[i-1][j] + abs(a[i] - k);
                path[i][to] = k;
            }
        }
    int s = 0, mn = inf;
    for (int j = 0; j <= m; ++j) if (dp[n][j] < mn) {
        mn = dp[n][j];
        s = j;
    }
    for (int i = n; i >= 1; --i) {
        b[i] = path[i][s];
        s -= st[path[i][s]];
    }
    for (int i = 1; i <= n; ++i)
        cout << b[i] << " \n"[i==n];
}

int main() {
    fast;
    out();
    return 0;
}