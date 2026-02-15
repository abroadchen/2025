//
// Created by Psy.C on 2026/2/15.
//
/**
时间复杂度: O(2^s3)，指数级别
空间复杂度: O(s3)，递归深度
适用范围: s3较小的情况

int dp[100010][2010];  // dp[i][j+1000]: 前i个字符达到值j的方案数
const int offset = 1000;  // 偏移量，处理负数索引
dp[0][s2 + offset] = 1;  // 初始状态：0个字符，值为s2，方案数为1

// DP转移
for (int i = 0; i < str2.length(); i++) {
    if (str2[i] == '?') {
        // 对于问号，可以填+1或-1
        for (int val = -1000; val <= 1000; val++) {
            if (dp[i][val + offset] > 0) {
                // 填'+'：值+1
                dp[i+1][val + 1 + offset] += dp[i][val + offset];
                // 填'-'：值-1
                dp[i+1][val - 1 + offset] += dp[i][val + offset];
            }
        }
    } else {
        // 对于已知字符，直接转移
        for (int val = -1000; val <= 1000; val++) {
            if (dp[i][val + offset] > 0) {
                if (str2[i] == '+') {
                    dp[i+1][val + 1 + offset] = dp[i][val + offset];
                } else {  // str2[i] == '-'
                    dp[i+1][val - 1 + offset] = dp[i][val + offset];
                }
            }
        }
    }
}

// 计算结果
int valid_ways = dp[str2.length()][s1 + offset];
double probability = (double)valid_ways / pow(2, s3);
printf("%.12f\n", probability);

int dp[2010][2010];  // dp[i][j+1000]: 前i个问号达到相对值j的方案数
const int offset = 1000;
// 只对问号进行DP
dp[0][0 + offset] = 1;  // 0个问号，相对值0，方案数1

for (int i = 1; i <= s3; i++) {
    for (int val = -s3; val <= s3; val++) {
        // 从前一个状态转移
        if (val - 1 >= -s3) dp[i][val + offset] += dp[i-1][val - 1 + offset];  // 填+
        if (val + 1 <= s3) dp[i][val + offset] += dp[i-1][val + 1 + offset];   // 填-
    }
}

// 目标相对值
int target_diff = s1 - s2;
if (abs(target_diff) > s3) {
    cout << "0.000000000000\n";
} else {
    double probability = (double)dp[s3][target_diff + offset] / pow(2, s3);
    printf("%.12f\n", probability);
}
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int s1, s;///s1:目标值，s:计数器
void dfs(const int ss, const int x) {//ss:剩余问号数，x:当前值
    if (ss == 0) {
        if (x == s1) s++;//当前值等于目标值
        return;
    }
    dfs(ss-1, x+1);//问号填'+'
    dfs(ss-1, x-1);//问号填'-' 当前值-1
}

int s2, s3;
string str1, str2;
int main() {
    fast;
    cin >> str1 >> str2;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] == '+') s1++;
        if (str1[i] == '-') s1--;
    }
    for (int i = 0; i < str2.length(); ++i) {
        if (str2[i] == '+') s2++;
        if (str2[i] == '-') s2--;
        if (str2[i] == '?') s3++;
    }
    const int k = s3;
    if (s3 == 0) {
        if (s2 == s1) cout << "1.000000000000\n";//完全匹配概率为1
        else cout << "0.000000000000\n";
    } else {
        dfs(s3, s2);//从s2开始，枚举s3个问号的所有填法
        const double ans = s*1./pow(2, k);//概率 = 符合条件的方案数 / 总方案数
        printf("%.12f\n", ans);
    }
    return 0;
}