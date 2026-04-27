//
// Created by Psy.C on 2026/4/27.
//
/**
ll pos = 1：初始化位置指针为1
for (ll i = 1; i <= n; i++)：从位置1到n循环
while (pos <= n && a[pos] == 'U') pos++;：
当pos不超过n且当前位置字符是'U'时
不断移动pos指针向右
if (pos > n) break;：如果pos超出范围，跳出循环
ans[i] = ans[i-1] + (pos-(i-1))*2-1;：
计算当前位置的答案值
公式含义：前一个位置的答案 + 距离相关的计算
(pos-(i-1))*2-1：距离因子的计算方式
pos++;：移动pos指针到下一个位置
pos = n;：将位置指针重置为n（字符串末尾）
for (ll i = n; i >= 1; i--)：从位置n到1倒序循环
while (pos >= 1 && a[pos] == 'D') pos--;：
当pos不小于1且当前位置字符是'D'时
不断移动pos指针向左
if (pos < 1) break;：如果pos小于1（越界），跳出循环
ans[i] = ans[i+1] + (n-pos+1-(n-i))*2-1;：
更新当前位置的值
使用后一个位置的值进行计算
距离计算公式略有不同
pos--;：将pos指针向左移动一位
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e6+7;
ll n, ans[N];
char a[N];
int main() {
    memset(ans, 0, sizeof(ans));
    cin >> n; scanf("%s", a + 1);
    ll pos = 1;
    for (ll i = 1; i <= n; i++) {
        while (pos <= n && a[pos] == 'U') pos++;
        if (pos > n) break;
        ans[i] = ans[i-1] + (pos-(i-1))*2-1;
        pos++;
    }
    pos = n;
    for (ll i = n; i >= 1; i--) {
        while (pos >= 1 && a[pos] == 'D') pos--;
        if (pos < 1) break;
        ans[i] = ans[i+1] + (n-pos+1-(n-i))*2-1;
        pos--;
    }
    for (ll i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}