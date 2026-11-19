//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
(n+i-1)/i 在整数除法下就是 ⌈n/i⌉（n 除以 i 向上取整）‍。
所以每个 i 算的是 ceil(n/i) + i，循环里对所有 i 取最小，输出最小值
i <= n/i 等价于 i*i <= n，即 i ≤ ⌊√n⌋，所以 i 只需枚举到根号 n。
这来自对称性：ceil(n/i) 和 ceil(n/j) 的函数 f(i)=ceil(n/i)+i 在 i > √n 之后的取值，已经能被前半段覆盖到（i 和 ceil(n/i) 的角色互换，min 不会出现在 i>√n 段）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, ans = INT_MAX;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n/i; ++i) ans = min(ans, (n+i-1)/i+i);
    cout << ans << '\n';
    return 0;
}