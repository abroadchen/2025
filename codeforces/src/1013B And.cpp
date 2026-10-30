//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n：输入数字个数；t：某个目标值。
flg：结果标记（初始 0，后来被重赋多种值）。
x[i]：读入的数。
y[i] = x[i] & t：每个输入数 x[i] 的最低几位（按 t 的二进制位掩码）结果。
b[ ]：记录 x[i] 原值出现次数的桶。
b2[ ]：记录 y[i]（即 x[i]&t）出现次数的桶
对每个数：
计算 y[i] = x[i] & t。
b[x[i]] 自增：统计原数出现次数。
b2[y[i]] 自增：统计与运算结果出现次数。
若某原数 x[i] 出现次数 >1，则 flg=2（存在重复原值）
若读入阶段就检测到重复原值（flg==2）→ 输出 flg-2 = 0 并直接结束。
所以读入阶段若发现重复原值，测试用例直接判为结果是 0
第二次遍历每个元素，判断两件事：

b[x[i]&t] > 0 且 (x[i]&t) != x[i] —— 即"某个数的 &t 结果存在另一个原值恰好等于这个 &t 值"（说明 x[i]&t 出现在输入中，但它与 x[i] 不同），此时记 flg=1 并立即 break。

含义：存在某个元素，其与 t 的掩码结果本身也是输入中的其他数，且这两个数不相等 → 对应某个需要判 1 的事件。
b2[y[i]] > 1 —— 若 y[i]（即 x[i]&t）这个值出现过多次，则 flg=2（覆盖式，非 break）。

最后输出 flg（初始 -1，可能被设为 1 或 2）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

ll n, t, flg, x[N], y[N], b[N], b2[N];
int main() {
    fast;
    cin >> n >> t;
    rep(i,n) {
        cin >> x[i]; y[i] = x[i]&t;
        b[x[i]]++; b2[y[i]]++;
        if (b[x[i]] > 1) flg = 2;
    }
    if (flg) { cout << flg-2 << '\n'; return 0; }
    flg = -1;
    rep(i,n) {
        if (b[x[i]&t] && (x[i]&t) != x[i]) { flg = 1; break; }
        if (b2[y[i]] > 1) flg = 2;
    }
    cout << flg << '\n';
    return 0;
}