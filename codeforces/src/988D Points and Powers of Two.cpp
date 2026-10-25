//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
非常大的数组大小（约20MB）
读入n个数，存入a[1..n]
排序（升序）
mx初始为1（至少能找到1个数），p,q用于存储二元组的两个值
a[k1] == x：x确实存在于数组中
a[k2] == y：y确实存在于数组中
各种边界检查确保k1,k2在有效范围内
如果找到： 输出3和三个数 x, a[i], y
如果只找到 x = a[i] + 2^j 在数组中：记录二元组 (a[i], x)
如果只找到 y = a[i] - 2^j 在数组中：记录二元组 (y, a[i])
mx设为2，表示找到了二元组
注意：

这个逻辑是贪心的，会不断更新p,q，后找到的会覆盖之前的
由于循环顺序，会记录最后一对满足条件的二元组
mx == 1：没找到任何等差对，输出1和排序后第一个数
mx == 2：找到二元组，输出两个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep0(i,n) for (i=0; i<n; i++)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e7+5;

int n, i, a[N], j, mx(1), p, q;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    sort(a+1, a+n+1);
    rep(i,n) {
        rep0(j,51) {
            int x = a[i] + pow(2,j), y = a[i] - pow(2,j),
            k1 = lower_bound(a+1,a+n+1,x)-a,//第一个≥x的位置
            k2 = lower_bound(a+1,a+n+1,y)-a;
            if (a[k1] == x && a[k2] == y && k1 >= 1 && k2 >= 1 && k1 <= n && k2 <= n) {
                cout << 3 << '\n';
                cout << x << ' ' << a[i] << ' ' << y << '\n';
                return 0;
            }
            if (a[k1] == x && k1 >= 1 && k1 <= n) { mx = 2; p = a[i], q = x;}
            else if (a[k2] == y && k2 >= 1 && k2 <= n) { mx = 2; p = a[i], q = y; }
        }
    }
    if (mx == 1) { cout << 1 << '\n'; cout << a[1]; }
    else if (mx == 2) { cout << 2 << '\n'; cout << p << ' ' << q; }
    return 0;
}