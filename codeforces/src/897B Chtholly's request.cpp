//
// Created by Psy.C on 2026/10/10.
//
/**
对每个 i：

t = i，进入循环：
q = q*10 + t%10：把 t 的个位依次拼到 q 前，最终 q 是 i 的倒序数
t /= 10：去掉个位
o *= 10：o 记录 i 有多少位（10 的幂）
举例：i = 123：

过程后 q = 321（倒序），o = 1000
sum = 123*1000 + 321 = 123000 + 321 = 123321
可见 sum 是把 i 和它自身倒序拼接成的偶数位回文数（如 1→11，12→1221，123→123321）。
ans = ans%p + sum：累加（先对已累积的部分取模，防止溢出）

ans = ans%p + sum 存在细节问题：它只在 ans 上取模，sum 和加法本身没有取模，ans%p 后加 sum 可能仍超过 ll 或超过 p。最后输出前又做了一次 cout << ans%p 兜底，所以最终结果正确，但中间 ans 变量会累积很大，存在溢出隐患。
复杂度：
O
(
k
⋅
log
⁡
10
k
)
O(k⋅log
10
​
 k)，因为每个 i 需要按位数遍历。
数据范围：若 k 很大（如
10
9
10
9
 ），这种逐数枚举会超时，通常需要找数学规律（如按位数分组求和）来优化
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll k, ans, p;
void solve() {
    for (ll i = 1; i <= k; ++i) {
        ll t = i, q = 0, o = 1;
        while (t) {
            q = q*10 + t%10;//求倒过来的数
            t /= 10;
            o *= 10;//用于回文数的拼接
        }
        ll sum = i*o+q;//拼接
        ans = ans%p+sum;
    }
}


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    k = rd(), p = rd(); solve();
    cout << ans%p;
    return 0;
}