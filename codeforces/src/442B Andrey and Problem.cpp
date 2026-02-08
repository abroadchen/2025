//
// Created by Psy.C on 2026/2/8.
//
/**
ans * (1 - a[i]): 原来的ans发生，当前元素不发生的概率
a[i] * pre: 当前元素发生，之前"其余部分"发生的概率
ans * (1 - a[i]) + a[i] * pre: 新的总概率
pre * (1 - a[i]): 更新pre，表示所有"其余部分"都未发生的概率
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    double a[110];//存储n个概率值
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    //排序后最大的概率值 互补概率
    double ans = a[n], pre = 1 - a[n];
    for (int i = n - 1; i > 0; --i) {
        if (ans * (1 - a[i]) + a[i] * pre >= ans) {//加入当前元素是否能提升结果
            ans = ans * (1 - a[i]) + a[i] * pre;
            pre = pre * (1 - a[i]);
        }
    }
    cout << fixed << setprecision(12) << ans;
    return 0;
}