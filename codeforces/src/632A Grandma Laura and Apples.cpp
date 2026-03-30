//
// Created by Psy.C on 2026/3/30.
//
/**
a[i] = 1 表示 "half" (1/2)
a[i] = 2 表示 "halfplus" (3/2 = 1 + 1/2)
t 统计 "halfplus" 的数量

循环从倒数第二个元素开始，构建一个二进制数：
遇到 "half" (1/2) → 左移一位 (相当于乘2)
遇到 "halfplus" (3/2) → 左移一位加1 (相当于乘2加1)

ans * p 是把每个 3/2 当作 2、每个 1/2 当作 1 来计算的结果
但实际 3/2 只是比 1 多了 1/2
所以要减去 t * (p/2)，即 t 个 "halfplus" 多算的 1/2 部分
最终结果：ans * p - t*(p/2) 计算的是 f[0] * f[1] * ... * f[n-1] * p 的精确整数值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, p;
string s;
ll a[50];
int main() {
    fast;
    cin >> n >> p;
    ll ans = 1, t = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        if (s == "half") a[i] = 1;
        else a[i] = 2, t++;
    }
    for (int i = n - 2; i >= 0; --i) {
        if (a[i] == 1) ans <<= 1;
        else ans = ans<<1|1;
    }
    ans = ans * p - t*(p/2);
    cout << ans << '\n';
    return 0;
}