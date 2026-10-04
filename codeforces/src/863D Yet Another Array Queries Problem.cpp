//
// Created by Psy.C on 2026/10/4.
//
/**
n 数组长度，q 操作个数，m 查询个数。
a：原始数组。
t[i], l[i], r[i]：第 i 个操作的类型和区间
对每个查询的初始位置 x，从第 q 个操作倒推到第 1 个操作，把 x 逆向映射：

操作 t=1（循环右移）的逆变换

循环右移 [l..r] 后，位置上元素来自哪里？

原位置 l+1..r 的元素移到 l..r-1，原位置 l 的元素移到 r。
逆向：如果当前 x 满足 l+1 ≤ x ≤ r（即最终落在原 l..r-1），则它来自 x-1，所以 x--。
如果 x == l，则它来自 r，所以 x = r。
两分支通过 t[j]==1 && x<=r[j] && x>=l[j]+1 和 t[j]==1 && x==l[j] 实现。
操作 t=2（翻转）的逆变换

翻转 [l..r] 后，位置 pos 的元素来自对称位置 l+r-pos。

如果 l ≤ x ≤ r，则 x = l + r - x。
不属于区间则不变

如果 x 不在操作区间内，无论哪类操作，位置不受影响，保持不变。

倒推结束后，x 就还原成原始数组中的下标，直接 cout << a[x] 输出原始值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int a[N], t[N], l[N], r[N];
int main() {
    fast;
    int n, q, m; cin >> n >> q >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= q; ++i) cin >> t[i] >> l[i] >> r[i];
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        for (int j = q; j >= 1; --j) {
            if (t[j] == 1 && x <= r[j] && x >= l[j]+1) x--;
            else if (t[j] == 1 && x == l[j]) x = r[j];
            else if (t[j] == 2 && x <= r[j] && x >= l[j]) x = l[j] + r[j] - x;
        }
        cout << a[x] << ' ';
    }
    return 0;
}