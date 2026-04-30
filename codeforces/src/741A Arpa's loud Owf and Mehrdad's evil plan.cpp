//
// Created by Psy.C on 2026/4/29.
//
/**
将b赋值给临时变量c，然后更新b为a%b，a为c
n: 输入的数组长度
a[N]: 存储输入数据的数组
i: 循环变量
sum: 结果变量，初始化为1
vis[N]: 访问标记数组，记录元素是否被访问过
flag: 标记是否有异常情况

遍历每个未访问的位置：如果位置i已访问则跳过
构建环：从位置i开始，跟踪序列i → a[i] → a[a[i]] → ...直到回到i
标记访问：将经过的每个元素标记为已访问
计数环长度：统计环中元素的数量
防止无限循环：如果循环次数超过n，说明有错误，设置flag
处理偶数长度环：如果是偶数长度，将其除以2
更新结果：将当前环长度与sum进行最小公倍数运算
如果出现异常情况(flag=true)，输出-1
否则输出最终计算的结果sum
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll c = b; b = a % b; a = c;
    }
    return a;
}
constexpr int N = 107;
ll n, a[N], i, sum = 1;
bool vis[N], flag;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> a[i];
    for (i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ll x = a[i]; vis[a[i]] = true;
        ll cnt = 1;
        while (x != i) {
            x = a[x]; vis[x] = true; cnt++;
            if (cnt > n) { flag = true; break; }
        }
        if (flag) break;
        if (cnt%2 == 0) cnt /= 2;
        sum = sum*cnt/gcd(cnt, sum);
    }
    if (flag) { cout << "-1\n"; return 0; }
    cout << sum << '\n';
    return 0;
}