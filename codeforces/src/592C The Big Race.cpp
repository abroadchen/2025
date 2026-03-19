//
// Created by Psy.C on 2026/3/19.
//
/**
t：总的时间或总数量
w：白色物品的数量
b：黑色物品的数量
确保w ≥ b，即让w始终是较大的值
计算w和b的最大公约数
tw = w/gcd：计算w除以其与b的GCD的商
lcm = tw*b：计算w和b的最小公倍数（利用公式：lcm(a,b) = a*b/gcd(a,b) = (a/gcd)*b）

条件判断：验证lcm/w/gcd == b，这是验证LCM计算的正确性
ans = t/lcm*min(w, b);：
t/lcm：计算t中有多少个完整的LCM周期
min(w, b)：取w和b中的较小值
整体：计算完整周期对答案的贡献
ull tmp = t/lcm*lcm;：计算完整周期所占用的总数
ans += min(min(w, b)-1, t - tmp);：
t - tmp：剩余的不完整部分
min(w, b)-1：考虑边界条件
取两者最小值加到答案中
如果LCM关系不满足，则直接取较小值减1和t的最小值
约分，将分数化为最简形式

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;

ull t, w, b;
int main() {
    fast;
    cin >> t >> w >> b;
    if (w < b) swap(w, b);
    ull gcd = __gcd(w, b), tw = w/gcd, lcm = tw*b, ans = 0;
    if (lcm/tw == b) {
        ans = t/lcm*min(w, b);
        ull tmp = t/lcm*lcm;
        ans += min(min(w, b)-1, t - tmp);
    } else ans = min(min(w, b)-1, t);
    ull div = __gcd(ans, t); ans/=div; t/=div;
    cout << ans << '/' << t << '\n';
    return 0;
}