//
// Created by Psy.C on 2026/10/10.
//
/**
x = n % 4，对 n 按模 4 分类。cnt 记录已放入结果数组 a 的个数，d 是一个附加输出值
n%4==0：d = 0，不预填
n%4==1：d = 1，预填一个 1
n%4==2：d = 1，预填一个 1
n%4==3：d = 0，预填 1 和 2
这个预填处理了余数带来的边界，保证后面成对填充时能对称
从 i = x+1 开始，步长 2，循环上限 x + (n-x)/2。每次放入两个数 i 和 n + x + 1 - i。

注意这一对的和：i + (n + x + 1 - i) = n + x + 1，是一个固定和。也就是说，代码把剩余的数配成若干对，每对之和 = n + x + 1，且总是"头尾/中间对称"地配
第一行输出 d，第二行输出元素个数 cnt 及全部元素
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e4+10;
int a[N];
int main() {
    fast;
    int n; cin >> n;
    int x = n%4, cnt = 0, d = 0;
    if (x == 0) d = 0;
    else if (x == 1) { d = 1; a[cnt++] = 1; }
    else if (x == 2) { d = 1; a[cnt++] = 1; }
    else if (x == 3) { d = 0; a[cnt++] = 1; a[cnt++] = 2; }
    for (int i = x+1; i <= x+(n-x)/2; i += 2) {
        a[cnt++] = i;
        a[cnt++] = n + x + 1 - i;
    }
    cout << d << '\n' << cnt;
    for (int i = 0; i < cnt; ++i) cout << ' ' << a[i];
    return 0;
}