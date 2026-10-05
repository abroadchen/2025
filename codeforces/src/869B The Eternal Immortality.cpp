//
// Created by Psy.C on 2026/10/5.
//
/**
读入 a、b；
若 b-a >= 5（区间长度至少 5），直接输出 0 并结束。因为任一连续 5 个整数乘积必含因子 10（含有 2 和 5），末位为 0
否则（区间长度 ≤ 4），从 a+1 到 b 逐个把每个数对 10 取模（即取其末位）后连乘，并同样对 10 取模；
最后结果的末位就是答案（因为乘积对 10 取模即得末位）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;


signed main() {
    fast;
    int a, b; cin >> a >> b;
    if (b-a >= 5) { cout << 0; return 0; }
    int ans = 1;
    for (int i = a+1; i <= b; ++i)
        ans = ans*(i%10)%10;
    cout << ans;
    return 0;
}