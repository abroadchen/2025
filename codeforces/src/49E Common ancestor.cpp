//
// Created by Psy.C on 2025/10/13.
//
/*
*s1[N], s2[N]：存储两个输入字符串（从索引1开始）
vp：存储产生式规则的向量
flag1[N][N], flag2[N][N]：记录子串能推导出的字符（状态压缩）
dp[N][N]：动态规划表，dp[i][j]表示匹配s1前i个字符和s2前j个字符的最少步数
 *
 *初始化：每个单个字符可以推导出自身
 *区间DP：从短区间到长区间计算
 *分割点枚举：尝试所有可能的分割点k
 *
*1 << (str[i] - 'a')：将字符编码为二进制位
(x >> o1 & 1)：检查第o1位是否为1
 *
*(i-1,j-1)：当前已匹配的位置
(p,q)：尝试匹配的新区间
flag1[i][p] & flag2[j][q]：检查两个子串是否能推导出相同字符
dp[p][q] = min(dp[p][q], dp[i - 1][j - 1] + 1)：更新DP状态
 *
 *
 *
*str[0] 对应产生式的左侧（结果字符）- 'A'
str[3] 和 str[4] 对应产生式的右侧（两个输入字符）- 'a' 和 'b'
 *'A'-'a' = 0, 'B'-'a' = 1, ... 'Z'-'a' = 25
 *
 *按照区间长度从小到大的顺序处理所有可能的子区间
*外层循环 i = 4:
  内层循环 j = 5: (无执行，因为j > n)

外层循环 i = 3:
  内层循环 j = 4: 处理区间 [3,4]

外层循环 i = 2:
  内层循环 j = 3: 处理区间 [2,3]
  内层循环 j = 4: 处理区间 [2,4]

外层循环 i = 1:
  内层循环 j = 2: 处理区间 [1,2]
  内层循环 j = 3: 处理区间 [1,3]
  内层循环 j = 4: 处理区间 [1,4]
 *
*按照区间长度排序：

长度2的区间：[3,4], [2,3], [1,2]
长度3的区间：[2,4], [1,3]
长度4的区间：[1,4]
为什么采用这种顺序？
在区间DP中，我们需要确保在计算大区间之前已经计算了所有可能的小区间：
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 5e1+10, M = 26;
char s1[N], s2[N];
vector<tuple<int,int,int>> vp;
int flag1[N][N], flag2[N][N], dp[N][N];

void build(char str[N], int flag[N][N]) {
    int n = strlen(str + 1);
    for (int i = 1; i <= n; ++i) flag[i][i] |= 1 << (str[i] - 'a');
    for (int i = n; i >= 1; --i) {
        for (int j = i + 1; j <= n; ++j) {
            int res(0);
            for (int k = i; k < j; ++k) {
                int x = flag[i][k], y = flag[k + 1][j];
                for (auto& [o1, o2, t] : vp) {
                    if ((x >> o1 & 1) && (y >> o2 & 1)) res |= t;
                }
            }
            flag[i][j] = res;
        }
    }
}

int main() {
    scanf("%s", s1 + 1); scanf("%s", s2 + 1);
    int k; scanf("%d", &k); vp.resize(k);

    for (auto& [a, b, c] : vp) {
        char str[10]; scanf("%s", str);
        c = str[0] - 'a';
        a = str[3] - 'a';
        b = str[4] - 'a';
        c = 1 << c;//使用左移运算将数字索引转换为对应的二进制位
    }
    build(s1, flag1); build(s2, flag2);
    int n = strlen(s1 + 1), m = strlen(s2 + 1);
    memset(dp, 0x3f, sizeof(dp));
    int inf = dp[0][0]; dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dp[i - 1][j - 1] == inf) continue;
            for (int p = i; p <= n; ++p) {
                for (int q = j; q <= m; ++q) {
                    if (flag1[i][p] & flag2[j][q])
                        dp[p][q] = min(dp[p][q], dp[i - 1][j - 1] + 1);
                }
            }
        }
    }
    int ans = dp[n][m];
    if (ans == inf) ans = -1;
    printf("%d\n", ans);
    return 0;
}