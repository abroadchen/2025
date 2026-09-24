//
// Created by Psy.C on 2026/9/22.
//
/**
t1 计算的是等差数列求和 1+2+...+(x-1)，用乘除避免溢出、并按奇偶分开写避免非整除时丢失精度：
等差数列和 S = x(x-1)/2。
当 x 为奇数时 x-1 为偶数，写成 x * ((x-1)>>1)。
当 x 为偶数时 x 为偶数，写成 (x>>1) * (x-1)。
t2 = n - x。
返回 min(t1, t2) + (n - x)
初始 l = 0, r = n。
三分法：取两个三等分点 lm、rm。
若 f(lm) > f(rm)，说明最小值在右半段（lm 右侧），收缩 r = rm；否则收缩 l = lm。
循环结束时区间缩到相邻两点，输出 f(l)。
三分法成立的前提是 f(x) 在定义域上是单峰函数（凸函数）‍，即先递减后递增（或先递增后递减）。这里代码假设 f(x) 是单谷（先减后增），在 [0, n] 上二分缩小找到最小值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n;
int f(int x) {
    int t1;
    if (x&1) t1=x*((x-1)>>1);
    else t1=(x>>1)*(x-1);
    int t2 = n-x;
    return min(t1, t2) + (n-x);
}

int rd() {
    int x; cin >> x;
    return x;
}

signed main() {
    fast;
    int q = rd();
    while (q--) {
        n = rd();
        int l = 0, r = n;
        if (n == 1) { cout << 0 << '\n'; continue; }
        while (l + 1 < r) {
            int lm = (l+r)>>1, rm = (lm+r)>>1;
            if (f(lm) > f(rm)) r = rm;
            else l = lm;
        }
        cout << f(l) << '\n';
    }
    return 0;
}