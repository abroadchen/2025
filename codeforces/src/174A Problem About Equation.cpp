//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 人数
b: 初始拥有的总资源量
 *d[i]表示第i个人当前拥有的资源
*x: 平均分配后每个人应该拥有的资源量
f: 标志位，表示是否可以完成分配
 *
*如果任何一个人当前拥有的资源已经超过平均值，则无法通过给予资源达到平衡（因为只能给予不能拿走）
如果可以分配，计算每个人需要获得多少资源：x - d[i]
 */
#include <iomanip>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; double b; cin>>n>>b;
    vector<double> d(n, 0);
    for (int i = 0; i < n; ++i) {
        cin>>d[i];
        b += d[i];
    }
    const double x = b / n; bool f = true;
    for (int i = 0; i < n; ++i) {
        if (d[i] > x) { f = false; break; }
        d[i] = x - d[i];
    }
    if (f) {
        for (int i = 0; i < n; ++i)
            cout << fixed << setprecision(6) << d[i] << '\n';
    } else cout << "-1\n";
    return 0;
}