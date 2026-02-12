//
// Created by Psy.C on 2026/2/12.
//
/**
n：矩阵大小（n×n）
d1[N<<1]：对角线1的和（主对角线方向，大小为2N）
d2[N<<1]：对角线2的和（反对角线方向，大小为2N）
b[N][N]：输入的n×n矩阵
t[2]：记录两种类型的最大值（根据坐标和的奇偶性）
ans[2]：记录两种类型的最佳位置
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2002
#define ii pair<int, int>
using namespace std;

int n;
ll d1[N<<1], d2[N<<1], b[N][N], t[2];
ii ans[2];

int main() {
    fast;
    cin >> n;
    memset(d1, 0, sizeof(d1));
    memset(d2, 0, sizeof(d2));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> b[i][j];
            d1[i+j] += b[i][j];//i+j相等的点在同一条对角线上
            d2[i-j+n] += b[i][j];//i-j相等的点在同一条对角线上
        }
    t[0] = t[1] = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (const ll v = d1[i+j] + d2[i-j+n] - b[i][j]; v > t[(i+j)&1]) {//坐标和的奇偶性
                t[(i+j)&1] = v;
                ans[(i+j)&1].first = i;
                ans[(i+j)&1].second = j;
            }
        }
    cout << t[0] + t[1] << '\n';
    cout << ans[0].first << ' ' << ans[0].second << ' ' << ans[1].first << ' ' << ans[1].second << '\n';
    return 0;
}