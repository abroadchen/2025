//
// Created by Psy.C on 2026/3/15.
//
/**
sum += a[i] - x：计算累积和，每次加上(a[i] - x)
res = max(res, fabs(sum - mn))：计算当前sum与最小值的差的绝对值
res = max(res, fabs(sum - mx))：计算当前sum与最大值的差的绝对值
更新mn和mx：记录累积和的最小值和最大值
返回res：累积和与极值的偏差的最大绝对值
l为所有元素绝对值的负数的最小值，r = -l

m1, m2：将区间[l,r]三等分的两个分割点
a1 = check(m1), a2 = check(m2)：计算两个分割点处的函数值
比较a1和a2：如果a1 < a2，说明最优解在右半部分，所以r = m2；否则l = m1
为什么使用三分搜索：

函数check(x)关于x是凸函数（或凹函数）
存在一个最优的x值使check(x)达到最小值
三分搜索可以找到单峰函数的极值点

时间复杂度
三分搜索：O(log²ε)，其中ε是精度要求
每次check函数：O(n)
总体：O(n × 迭代次数) = O(400n)
空间复杂度
O(n)：存储输入数组

将原数组减去一个公共偏移量x
计算累积和序列
找到使累积和序列波动最小的偏移量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int n;
double a[N];
double check(double x) {
    double sum = 0, res = 0, mn = 0, mx = 0;
    for (int i = 1; i <= n; ++i) {
        sum += a[i] - x;
        res = max(res, fabs(sum - mn));
        res = max(res, fabs(sum - mx));
        mn = min(mn, sum);
        mx = max(mx, sum);
    }
    return res;
}

int main() {
    fast;
    cin >> n;
    double l = 0, r;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) l = min(l, -fabs(a[i]));
    r = -l;
    int cnt = 0;
    while (cnt++ < 400) {
        double m1 = l + (r - l)/3, m2 = r - (r - l)/3,
        a1 = check(m1), a2 = check(m2);
        if (a1 < a2) r = m2; else l = m1;
    }
    printf("%.6lf\n", check((l+r)/2.));
    return 0;
}