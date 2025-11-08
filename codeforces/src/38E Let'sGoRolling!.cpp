//
// Created by Psy.C on 2025/9/23.
//
/*
*d[i + 1][i] + a[i].second: 先访问第i个点，再访问第i+1个点，代价是第i个点的y坐标
d[i + 1][j] + a[i].first - a[j].first: 先访问第i个点，再回到第j个点，代价是两点x坐标差值
 *
 *
 */
#include <algorithm>
#include <ios>
#include <iostream>
using namespace std;
const int N = 3005;
int d[N][N];//动态规划的状态存储
pair<int, int> a[N];//存储坐标点对

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);//索引0未使用 默认按first元素（x坐标）升序排序
    a[0] = make_pair(-1e9, -1e9);//极小值点，作为边界条件
    //d[i][j]表示从第i个点开始，前一个访问的点是第j个点时的最小代价
    for (int i = n; i >= 1; --i)
        for (int j = 0; j < i; ++j)
            d[i][j] = min(d[i + 1][i] + a[i].second,
                d[i + 1][j] + a[i].first - a[j].first);
    cout << d[1][0];//从第1个点开始，之前访问的是第0个点的最小代价
    return 0;
}