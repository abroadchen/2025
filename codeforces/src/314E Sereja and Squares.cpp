/**
 *
* 1. 为什么有 i - t？
i 是当前处理到字符串的位置（从1开始）
t 是字符串总长度的一半（n/2）
i - t 表示：当前处理到第i个字符，考虑到对称性，最多可能与前半部分形成 i - t 对匹配
2. 为什么有 1？
j 是dp数组的索引，表示匹配对的数量
匹配对数量不能为负数或0以下，所以最小是1（如果存在匹配的话）
保证 j >= 1
3. 实际含义
当 i <= t 时（还在前半部分），i - t <= 0，所以 max(1, i-t) = 1
当 i > t 时（开始处理后半部分），i - t > 0，表示从后半部分第 i-t 个字符开始可能与前半部分匹配
 *
* t 是期望的匹配对数（n/2）
cnt 是已确定的匹配对数（非'?'字符数）
t - cnt 是剩余需要填充的'?'对数
每对'?'有25种可能的填法
 */
#include <iostream>
#define N 100005
using namespace std;


int main() {
    int n; scanf("%d",&n);
    if (n & 1) return putchar('0'), 0;
    char s[N]; scanf("%s", s + 1);
    unsigned int dp[N]; dp[0] = 1;
    int cnt = 0;//非'?'字符的数量
    const int t = n>>1;
    for (int i = 1; i <= n; ++i) {//遍历字符串的每个位置
        if (s[i] == '?') {
            for (int j = i>>1, x = max(1, i - t);  j >= x; --j) dp[j] += dp[j - 1];
        } else cnt++;
    }
    if (t < cnt) return putchar('0'), 0;
    for (int i = t - cnt; i--;) dp[t] *= 25;//?'字符可以填入25个不同字母
    printf("%u", dp[t]);
    return 0;
}