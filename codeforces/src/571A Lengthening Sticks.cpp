//
// Created by Psy.C on 2026/3/13.
//
/**
l：输入的长度参数，d：循环变量
get函数：计算满足特定条件的整数解数量
x = min(l + a - d, d - b - c)：计算限制条件下的最大值
如果x<0返回0，否则返回组合数(x+2)(x+1)/2
mx：a, b, c中的最大值
ans：初始化为总的非负整数解数量（三维单纯形体积公式）
从mx遍历到mx+l
对每种排列计算并减去不满足条件的解数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int l, d;
ll get(int a, int b, int c) {
    int x = min(l + a - d, d - b - c);
    return x < 0 ? 0 : 1ll*(x+2)*(x+1)/2;
}

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c >> l;
    int mx = max(a, max(b, c));
    ll ans = 1ll*(l+3)*(l+2)/2*(l+1)/3;
    for (d = mx; d <= mx + l; ++d)
        ans -= get(a, b, c) + get(b, a, c) + get(c, a, b);
    cout << ans << '\n';
    return 0;
}