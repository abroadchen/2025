//
// Created by Psy.C on 2026/4/14.
//
/**
a, b: 两个间隔数
p, q: 两种颜色的权重
both: 同时被a和b整除的数的个数
n/lcm(a,b): 1到n中同时被a和b整除的数的个数
情况1：p < q（红色权重更小）
red = n/a - both: 只能被a整除的数（排除重叠）
blue = n/b: 所有能被b整除的数（包括重叠）
情况2：p ≥ q（蓝色权重更大或相等）
red = n/a: 所有能被a整除的数（包括重叠）
blue = n/b - both: 只能被b整除的数（排除重叠）

当p < q时，优先将重叠部分分配给蓝色（因为蓝色更贵）
当p ≥ q时，优先将重叠部分分配给红色（因为红色更贵或相等）
这样可以最小化总代价
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, a, b, p, q, red, blue, both;
int main() {
    fast;
    cin >> n >> a >> b >> p >> q;
    both = n/lcm(a,b);
    if (p < q) {
        red = n/a - both;
        blue = n/b;
    } else {
        red = n/a;
        blue = n/b - both;
    }
    cout << red*p + blue*q << '\n';
    return 0;
}