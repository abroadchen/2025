//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
n：排列的长度（位置个数）。
m：(x, d) 的对数。
sum：累计的总贡献（最后除以 n 得答案）。
x, d：每对输入参数。
mn、mx：两个预计算量
分 n 奇偶：
n 为奇数时，n/2*(n/2+1) 表示中间元素两侧距离和。
n 为偶数时额外减去 n/2（对称调整）
对于距离的某种全体对求和，mx 是最大可能值（当所有元素尽量分开时），其量纲是所有位置对的个数 C(n,2)
① 基础项 x * n
② 差值项（取决于 d 的符号）
若 d > 0：贡献与该对距离正相关，取距离最大（用 mx）时平均贡献最大，所以用 mx * d。
若 d ≤ 0：贡献与该对距离负相关，取距离最小（用 mn）时平均贡献最大（因为负 × 大距离会使结果变小），所以用 mn * d
把累计 sum 转成浮点 1.0*sum，再除以 n，得到每个位置的平均贡献
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, sum, mn, mx, x, d;
int main() {
    fast;
    cin >> n >> m;
    mn = n/2*(n/2+1)-(n%2?0:n/2), mx = n*(n-1)/2;
    while (m--) {
        cin >> x >> d;
        sum += x*n;
        if (d > 0) sum += mx*d; else sum += mn*d;
    }
    cout << fixed << setprecision(15) << 1.*sum/n << '\n';
    return 0;
}