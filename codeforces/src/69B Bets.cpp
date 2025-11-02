//
// Created by Psy.C on 2025/11/2.
//
/*
*n, m: 主要参数变量
i, j: 循环变量
l[N], r[N], t[N], c[N]: 大小为N的数组，存储输入数据
a[N], b[N], d[N]: 大小为N的数组，用于处理逻辑
sum: 累加和变量
 *
 *
 *读取n个位置和m个区间信息，每个区间有起始位置、结束位置、时间戳和代价。
 *对于每个位置j，选择时间戳最小的区间覆盖（时间相同时选择编号小的），
 *最后计算所选区间代价之和
 */
#include <iostream>
#define rep(i,n) for(i=1;i<=(n);++i)
using namespace std;

const int N = 1009, inf = 2147483647;
int n, m, i, j,
l[N], r[N], t[N], c[N],
a[N], b[N], d[N], sum;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    rep(i,n) a[i] = inf;
    rep(i,m) cin >> l[i] >> r[i] >> t[i] >> c[i];
    rep(i,m) {
        for (j = l[i]; j <= r[i]; ++j) {
            if (a[j] > t[i] || a[j] == t[i] && b[j] > i) {
                b[j] = i;
                a[j] = t[i];
                d[j] = c[i];
            }
        }
    }
    rep(i,n) sum += d[i];
    cout << sum;
    return 0;
}