//
// Created by Psy.C on 2025/12/6.
//
/*
*n：字符串长度
tag：初始状态（0或1）
a[]：字符数组（0表示'B'，1表示'A'）
初始化DP数组，dp[0][tag] = 1表示初始状态
 *
*如果a[i+1] == 0（字符'B'）：
dp[i+1][0] = dp[i][0]：保持状态0
如果a[i+1] == 1（字符'A'）：
如果a[i] == 1（前一个也是'A'）：
dp[i+1][1] = dp[i][0] + dp[i][1]：可以从状态0或1转移到状态1
如果a[i] == 0（前一个是'B'）：
dp[i+1][0] = dp[i-1][0] + dp[i-1][1]：状态0的转移
dp[i+1][1] = dp[i][0] + dp[i][1]：状态1的转移
 *
 *如果没有找到'B'或者'B'在倒数第二个位置之后，直接输出1
*将字符串从第一个'B'位置开始重新排列（循环移位）
a[i+1] = s[(i+pos)%n] == 'A'：转换为0/1数组
计算从状态0和状态1开始的方案数之和
 *
 *时间复杂度：O(n) 空间复杂度：O(n)
 *
 *字符串的循环左移：

原字符串：s[0] s[1] s[2] ... s[pos-1] s[pos] ... s[n-1]
移位后：s[pos] s[pos+1] ... s[n-1] s[0] s[1] ... s[pos-1]
 *
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 110, M = 2;

ll f(const int n, const int tag, const int a[]) {
    ll dp[N][M] = {}; dp[0][tag] = 1;
    for (int i = 0; i < n; ++i) {
        if (!a[i+1]) dp[i+1][0] = dp[i][0];
        else {
            if (a[i]) dp[i+1][1] = dp[i][0] + dp[i][1];
            else {
                dp[i+1][0] = dp[i-1][0] + dp[i-1][1];
                dp[i+1][1] = dp[i][0] + dp[i][1];
            }
        }
    }
    return dp[n][tag];
}


int main() {
    fast;
    char s[N];
    cin >> s;
    const int n = static_cast<int>(strlen(s));
    int a[N];
    const int pos = static_cast<int>(strcspn(s, "B"));//找到第一个'B'的位置
    if (pos >= n - 1) return cout << "1\n", 0;
    for (int i = 0; i < n; ++i) a[i+1] = s[(i+pos)%n] == 'A';
    cout << f(n, 0, a) + f(n, 1, a) << '\n';
    return 0;
}