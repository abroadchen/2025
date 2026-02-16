//
// Created by Psy.C on 2026/2/16.
//
/**
f: 当前位置是否能匹配字符串p
j: 匹配的起始位置
k-i+j+l2: 检查约束条件（删除的字符数是否合理）

预处理：对每个位置i，用check(i)计算是否能匹配p
DP转移：
继承前一状态
如果当前位置能匹配p，尝试使用这个匹配
输出：dp[l1][i]表示使用i个删除操作的最大匹配数

check函数：O(|s| × |p|) 每次
总体：O(|s|² × |p|)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2005;
char s[N], p[N];
int l1, l2, j;
int check(const int i) {//从位置i开始，反向匹配字符串p
    int x = i, y = l2;//x指向s，y指向p的末尾
    while (x && y) {//都不为0时循环
        //if (!y) break;
        if (s[x-1] == p[y-1]) { x--; y--; }//匹配成功，两指针同时移动
        else x--;//匹配失败，只移动s的指针
    }
    if (!y) { j = x; return 1; }//p完全匹配，记录结束位置
    j = 0;
    return 0;
}

int f, dp[N][N];//前i个字符中，使用恰好k个删除操作的最大匹配数
int main() {
    fast;
    cin >> s >> p; l1 = strlen(s); l2 = strlen(p);
    for (int i = 1; i <= l1; ++i) {
        f = check(i);
        for (int k = 0; k <= i; ++k) {
            dp[i][k] = max(dp[i-1][k], dp[i-1][k-1]);//不使用第i个字符或删除它
            if (f && j >= k-i+j+l2 && k-i+j+l2 >= 0)//当前有匹配
                dp[i][k] = max(dp[i][k], dp[j][k-(i-j-l2)]+1);//使用匹配
        }
    }
    for (int i = 0; i <= l1; ++i) cout << dp[l1][i] << ' ';
    return 0;
}