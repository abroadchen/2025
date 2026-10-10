//
// Created by Psy.C on 2026/10/10.
//
/**
求 a/b 的小数部分，就是不断做"长除法"取余数：

小数第 1 位 = (a*10) / b 的整数部分
然后 余数 = (a*10) % b
下一位 = (余数*10) / b 的整数部分
……
这正是竖式除法求小数的标准过程

ans 从 1 开始，表示当前判断的是小数第几位。

a*10/b%10：这是当前这一位小数。解释一下——a*10/b 得到的是一个数，但为什么 %10？

这里其实是利用了 a 已经被限制在 [0, b) 的范围（因为 a 始终是上一次的余数 < b），所以 a*10 < 10b，于是 a*10/b 是一个个位数（在 0..9 之间），%10 只是保险/明确取个位。它正是当前要生成的小数位。

若该位 不等于 c：更新 a = a*10%b（得到下一位的余数），ans++ 继续看下一位。

若该位 等于 c：输出 ans 并跳出（第一次出现的位置
若在 N = 10000 位内都没找到 c，输出 -1（表示在可接受范围内未找到）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4;
int a, b, c;
int main() {
    fast;
    while (cin >> a >> b >> c) {
        int ans = 1;
        while (ans < N) {
            if (a*10/b%10 != c) {
                a = a*10%b;
                ans++;
            } else {
                cout << ans << '\n';
                break;
            }
        }
        if (ans == N) cout << "-1\n";
    }
    return 0;
}