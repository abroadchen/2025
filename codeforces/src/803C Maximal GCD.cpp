//
// Created by Psy.C on 2026/9/19.
//
/**
n：目标值（要构造的某种总和/约束）。
k：要输出的正整数个数。
inf = 141420：一个常量上限（近似 141420，配合 (k+1)*k/2 的判定）。
循环读入多组 n k，每组调 get()
若 k > inf 直接不可行（防溢出/超大）。
sum = (k+1)*k/2 是 1+2+...+k 的和——需要最小可能的总和。
这说明：构造的 k 个正整数，其最小可行总值为 sum（1 到 k 各出现一次）
遍历 n 的因子对 (i, n/i)：

若 i >= sum → 取 q = n/i 并结束；
否则若 n/i >= sum → q = i（尽量保持 q 较小）。
目的：找到一个因子 q，使得 q * sum <= n（因为后面要用若干 q 的倍数填满 n）。若找不到满足的因子 → 输出 -1
前 k-1 个输出 1*q, 2*q, ..., (k-1)*q，并累计 ans = 1+2+...+(k-1)。
最后一个输出 q * (n/q - ans)，确保总和为 n。
验证总和：
q
(
1
+
2
+
⋯
+
(
k
−
1
)
)
+
q
(
n
q
−
(
1
+
2
+
⋯
+
(
k
−
1
)
)
)
=
q
⋅
n
q
=
n
q(1+2+⋯+(k−1))+q(
q
n
​
 −(1+2+⋯+(k−1)))=q⋅
q
n
​
 =n

因为前面保证 q 能整除 n（q 是因子），且 q*sum ≤ n，最后一个数为正整数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int inf = 141420;
ll n, k;
void get() {
    if (k > inf) { cout << "-1\n"; return; }
    ll sum = (k+1)*k/2, q = 0, sqr = sqrt(n);
    for (ll i = 1; i <= sqr; ++i) {
        if (n%i == 0) {
            if (i >= sum) { q = n/i; break; }
            if (n/i >= sum) q = i;
        }
    }
    if (!q) { cout << "-1\n"; return; }
    ll ans = 0;
    for (ll i = 1; i < k; ++i) {
        cout << i*q << ' ';
        ans += i;
    }
    cout << q*(n/q-ans) << '\n';
}


int main() {
    fast;
    while (cin >> n >> k) get();
    return 0;
}