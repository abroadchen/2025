//
// Created by Psy.C on 2026/3/4.
//
///时间复杂度为O(len)，空间复杂度为O(1)
/**
将4看作0，7看作1
"47" → "01" → 对应二进制数1
但在4-7数列中，还要考虑更短的数字
所以要加上前面所有较短数字的数量
+1是为了从"小于它的数量"转换为"它的排名"，就像数组下标从0开始改为从1开始一样

4-7数列：4(第1个), 7(第2个), 44(第3个), 47(第4个), 74(第5个), ...
计算过程：
sum[1] = 2（一位数：4, 7）
对于"47"：
第0位是'4'：无需加数
第1位是'7'：在两位数中，44之前的数量 = 2^1 = 2
ans = 2 + 1 = 3（小于"47"的数有：4, 7, 44）
ans + 1 = 4（"47"是第4个数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
char str[100];
ll sum[15];
int main() {
    fast;
    scanf("%s", str);
    int len = strlen(str);
    ll t = 1;
    for (int i = 1; i <= 9; ++i) {
        t <<= 1;
        sum[i] = sum[i-1] + t;//2^1 + 2^2 + ... + 2^i
    }
    ll ans = sum[len-1];
    for (int i = 0; i < len; ++i)
        if (str[i] == '7')
            ans += 1<<(len-i-1);//2^(len-i-1) 右侧位数
    cout << ans+1 << '\n';
    return 0;
}