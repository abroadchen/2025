//
// Created by Psy.C on 2026/9/4.
//
/**
递归计算
b
i
d
x
b
idx
 （不取模）。
思路：采用二分递归（Exponentiation by Squaring）：
若指数为奇数，结果为
b
⌊
i
d
x
/
2
⌋
×
b
⌊
i
d
x
/
2
⌋
×
b
b
⌊idx/2⌋
 ×b
⌊idx/2⌋
 ×b。
若指数为偶数，结果为
b
⌊
i
d
x
/
2
⌋
×
b
⌊
i
d
x
/
2
⌋
b
⌊idx/2⌋
 ×b
⌊idx/2⌋
 。
边界条件：
b
0
=
1
b
0
 =1,
b
1
=
b
b
1
 =b

ans：累计符合条件的 (p,q) 对数量。
L, R：当前固定 p 时，合法的 q 的范围下界和上界。
外层循环 (for (ll p = 2; p < r; ++p))：
枚举基准值 $p$，从 2 开始（因为要求
p
>
q
p>q）。
计算上界 R = r / p^{n-1}，即根据右边界 $r$ 限制的最大 $q$。
如果 R == 0，说明后续更大的 $p$ 将导致 p^{n-1} 超过 $r$，直接跳出循环（剪枝）。
内层循环 (for (ll q = 1; q < p; ++q))：
枚举小于 $p$ 的 $q$。
计算下界 L = (l-1)/q^{n-1} + 1，即根据左边界 $l$ 限制的最小 $q$。
如果 L > R，则此 $p$ 下无合法 $q$，继续下一个 $p$。
使用 __gcd(p, q) 检查是否互质（最大公约数为 1），这是题目要求。
若满足，则将该区间 [L, R] 中的所有整数都计入答案：ans += R - L + 1。
最终输出：cout << ans*2 << '\n';
因为每个合法 (p,q) 对对应两个有序对（(a,b) 与 (b,a)），所以乘以 2

读入数据：读取维度 $n$ 和区间端点 $l$, $r$。
特判与优化：
case 1：当 $n=1$ 时，方程退化为恒成立，答案是区间长度 $r-l+1$。
case 2：当 $n=2$ 时，答案是组合数 (r-l+1) * (r-l)（因为任意两数均可构成）。
默认情况（n >= 3）：
n > 40：若维度过高，指数增长导致搜索空间为空，直接输出 0。
否则调用 solve() 进行枚举计算

时间复杂度
O(r log r)
实际运行远低于 O(r²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll pw(ll b, ll idx) {
    if (idx == 1) return b;
    if (idx == 0) return 1ll;
    ll p = pw(b, idx/2);
    if (idx%2) return p*p*b;
    return p*p;
}

ll l, r, n;//区间端点和维度
void solve() {
    ll ans = 0, L, R;
    for (ll p = 2; p < r; ++p) {
        R = r/pw(p, n-1);
        if (R == 0) break;
        for (ll q = 1; q < p; ++q) {
            L = (l-1)/pw(q, n-1) + 1;
            if (L > R) continue;
            if (__gcd(p, q) == 1)
                ans += R - L + 1;
        }
    }
    cout << ans*2 << '\n';
}

int main() {
    fast;
    cin >> n >> l >> r;
    switch (n) {
        case 1:
            cout << r - l + 1 << '\n'; return 0;
        case 2:
            cout << (r - l + 1) * (r - l) << '\n'; return 0;
        default:
            (n > 40) ? (puts("0"), exit(0)) : (solve()); return 0;
    }
    return 0;
}