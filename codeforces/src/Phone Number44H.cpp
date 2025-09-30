//
// Created by Psy.C on 2025/9/28.
//
/*
 *dp[i][j]表示前i位数字以数字j结尾的满足条件的数字个数
*s[N]: 输入的字符串
a[N]: 将字符串转换为数字数组
n: 数字的位数
 *
 *初始化dp[1][i] = 1 (i=0~9)，表示第一位可以是任意数字
*计算第(i+1)位可能的数字：k(下界)和l(上界)
将状态转移到对应的数字上
 *
*(j + a[i + 1]) / 2 和 (j + a[i + 1] + 1) / 2 这两个表达式计算的是：

当前位数字j和目标位置数字a[i+1]的平均值的下界和上界
 *
 *
 *检查原始数字是否满足条件，如果满足则减去1（因为不包含原始数字本身）
 *
 *
 */
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 55, M = 10;
ll dp[N][M];
char s[N];
int n, a[N];

int main() {

    scanf("%s", s + 1); n = strlen(s + 1);

    for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
    for (int i = 0; i < 10; ++i) dp[1][i] = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 10; ++j) {
            int k = (j + a[i + 1]) / 2, l = (j + a[i + 1] + 1) / 2;
            dp[i + 1][k] += dp[i][j];
            if (k != l) dp[i + 1][l] += dp[i][j];
        }
    }

    ll ans(0);
    for (int i = 0; i < 10; ++i) ans += dp[n][i];
    int flag(1);
    for (int i = 2; i <= n; ++i) {
        if ((a[i - 1] + a[i]) / 2 == a[i] ||
            (a[i - 1] + a[i] + 1) / 2 == a[i]) continue;
        else {
            flag = 0;
            break;
        }
    }
    printf("%lld\n", ans-flag);
    return 0;
}