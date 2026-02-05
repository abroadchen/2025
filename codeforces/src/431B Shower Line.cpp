//
// Created by Psy.C on 2026/2/5.
//
/**
* c[6][6]: 5×5的权值矩阵
a[6]: 用于生成排列的数组
 *next_permutation需要初始序列为非递减序列
 *
*时间复杂度：O(5! × 常数) = O(120 × 常数)
空间复杂度：O(25)（主要是存储矩阵c）
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int c[6][6], a[6];
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j)
        cin >> c[i][j];
    for (int i = 0; i < 5; ++i) a[i] = i;
    ll res = 0;
    do {
        ll ans = 0;
        ans += (c[a[0]][a[1]] + c[a[1]][a[0]] + c[a[2]][a[3]] + c[a[3]][a[2]]) +
            (c[a[1]][a[2]] + c[a[2]][a[1]] + c[a[3]][a[4]] + c[a[4]][a[3]]) +
                (c[a[2]][a[3]] + c[a[3]][a[2]]) + (c[a[3]][a[4]] + c[a[4]][a[3]]);
        res = max(ans, res);
    } while (next_permutation(a, a + 5));
    cout << res;
    return 0;
}