//
// Created by Psy.C on 2026/8/25.
//
/**
- constexpr int N = 110 ：定义数组大小上限，支持最大长度 16*n ≤ 100 （n较小，避免 long long 溢出）。
- int c[N][N] ： 组合数表 ， c[i][j] 存储组合数 C(i,j) （从 i 个元素中选 j 个的方案数）。
- void init() ： 初始化组合数表 ，用杨辉三角递推：
- c[i][0] = 1 ：任何数选0个的方案数为1。
- c[i][j] = c[i-1][j] + c[i-1][j-1] ：杨辉三角核心公式， C(i,j) = C(i-1,j) + C(i-1,j-1)

- dp[N][N] ：动态规划数组， dp[i][j] 表示 前 i+1 个十六进制字符（ 0~i ）使用 j 个位置的方案数 。
- lim[16] ：每个十六进制字符的最大出现次数（初始为 n ）。
- int dfs(int len, bool flag) ： 计算合法字符串数量 的核心函数
- len ：剩余需要填充的位置总数。
- flag ：前导零标志：
- flag = 1 ：当前第一位不能为 0 （无前导零要求）。
- flag = 0 ：剩余位置可以为 0 （后续位置无此限制）

- memset(dp, 0, sizeof dp) ：清空DP数组，初始化为0。
- 初始化第一个字符（ 0 ）的状态 ：
处理字符 0 的放置方案：
- 若 flag=1 （第一位不能为 0 ）， 0 只能放在剩余 len-1 个位置，可用位置数为 len-1 （即 len-flag ）。
- 若 flag=0 （无限制）， 0 可放在所有 len 个位置，可用位置数为 len （即 len-flag ）。
- dp[0][i] = c[len-flag][i] ：从 len-flag 个位置中选 i 个放 0 的方案数

- 外层循环 i ：遍历十六进制字符 1~15 （共15个字符，加上 0 共16个）。
- 中层循环 j ：遍历已使用的位置数 0~len 。
- 内层循环 k ：遍历当前字符 i 使用的位置数 0~min(j, lim[i]) （不超过上限 lim[i] 和已用位置数 j ）。
- 状态转移方程 ：
- dp[i-1][j-k] ：前 i-1 个字符使用 j-k 个位置的方案数。
- c[len-(j-k)][k] ：从剩余 len-(j-k) 个位置中选 k 个放当前字符 i 的组合数。
- 累加所有可能的 k 值，得到 dp[i][j]
返回所有16个字符都考虑后，使用 len 个位置的方案数（即长度为 len 的合法字符串总数）

- k ：要求的第 k 个合法字符串（从1开始计数）。
- n ：每个十六进制字符的最大出现次数
设置字符上限
将 lim[0]~lim[15] 全部设为 n ，即每个十六进制字符最多出现 n 次

确定字符串长度 len
- 从长度 1 开始，逐长度计算合法字符串数量 cnt （ dfs(len,1) ， flag=1 避免前导零）。
- 若 cnt >= k ，说明第 k 个字符串在当前长度 len 中，退出循环。
- 否则 k -= cnt ，减去当前长度的方案数，继续搜索更长的长度

- 外层循环 i ：遍历每个位置（第1位到第 len 位）。
- 内层循环 j ：遍历每个可能的十六进制字符 j ：
- 第一位（ i==1 ）从 1 开始（避免前导零），其余位从 0 开始。
- lim[j]-- ：假设当前位置放 j ，减少 j 的剩余可用次数。
- int cnt = dfs(len - i, 0) ：计算剩余 len-i 个位置的合法字符串数量（ flag=0 ，后续位置无前置零限制）。
- 若 cnt >= k ：第 k 个字符串在当前位置放 j 的方案中，用 printf("%llx", j) 输出 j 的十六进制，然后 break 跳出当前位置的循环，处理下一位。
- 否则 k -= cnt ，减去当前 j 的方案数， lim[j]++ 恢复 j 的上限，尝试下一个字符

- 组合数初始化： O(100^2) 。
- 每次 dfs 的DP计算： O(16 * len^2) （三重循环）。
- 逐位确定： O(len * 16 * len^2) = O(16 * len^3)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 110;

int c[N][N];
void init() {
    for (int i = 0; i <= 100; ++i) c[i][0] = 1;
    for (int i = 1; i <= 100; ++i)
        for (int j = 1; j <= i; ++j)
            c[i][j] = c[i-1][j] + c[i-1][j-1];
}

int dp[N][N], lim[16];
int dfs(int len, bool flag) {
    memset(dp, 0, sizeof dp);
    for (int i = 0; i <= min(len - flag, lim[0]); ++i)
        dp[0][i] = c[len-flag][i];
    for (int i = 1; i < 16; ++i)
        for (int j = 0; j <= len; ++j)
            for (int k = 0; k <= min(j, lim[i]); ++k)
                dp[i][j] += dp[i-1][j-k] * c[len-(j-k)][k];
    return dp[15][len];
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int k, n;
signed main() {
    fast;
    k = rd(), n = rd(); init();
    int len;
    for (int &i : lim) i = n;
    for (len = 1; len <= 16*n; ++len) {
        int cnt = dfs(len, 1);
        if (cnt >= k) break;
        k -= cnt;
    }
    for (int i = 1; i <= len; ++i)
        for (int j = i == 1 ? 1 : 0; j < 16; ++j) {
            lim[j]--;
            int cnt = dfs(len - i, 0);
            if (cnt >= k) { printf("%llx", j); break; }
            k -= cnt;
            lim[j]++;
        }
    return 0;
}