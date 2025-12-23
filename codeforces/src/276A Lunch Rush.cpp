//
// Created by Psy.C on 2025/12/23.
//
/*
 * n(元素个数)、k(阈值)、f(分数)、t(时间)、mx(最大值)、ans(当前答案)
* 如果时间t超过阈值k，则计算调整后的分数f-(t-k) 实际分数 = 原分数 - (超时时间)
否则直接使用原始分数f
将结果存入mx作为初始最大值
 *
* 循环处理剩余的n-1个元素
读入当前元素的f和t
 *计算当前元素的调整后分数
 *如果当前分数大于最大值，更新最大值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, f, t, mx, ans; cin >> n >> k >> f >> t;
    if (t > k) mx = f - (t - k); else mx = f;
    while (--n) {
        cin >> f >> t;
        if (t > k) ans = f - (t - k); else ans = f;
        if (ans > mx) mx = ans;
    }
    cout << mx << '\n';
    return 0;
}