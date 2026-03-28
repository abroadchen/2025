//
// Created by Psy.C on 2026/3/27.
//
/**
n: 初始资源数量
a: 第一种操作的成本
b: 第二种操作的成本
c: 第二种操作获得的收益
ans: 存储最终结果

(b-c) < a 表示第二种操作的净成本小于第一种操作的成本
并且 n >= b 表示有足够的资源进行第二种操作
(n - b) / (b - c) 表示在保留至少b个资源的情况下，还能进行多少次净消耗为(b-c)的操作
加1是因为还可以进行一次初始的b单位消耗操作
更新剩余资源数量
ans += n/a;: 用剩余的n资源执行尽可能多的a单位消耗操作
输出总操作次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;

ull n, a, b, c, ans;
int main() {
    fast;
    cin >> n >> a >> b >> c;
    if (b - c < a && n >= b) {
        ans = (n - b) / (b - c) + 1;
        n -= (b - c) * ans;
    }
    ans += n/a;
    cout << ans;
    return 0;
}