//
// Created by Psy.C on 2026/1/20.
//
/**
* n（行数）、m（列数）、k（种类数）、s（序列长度）
a[10][5]：存储每种类型在4个方向上的最大值
 *
 *O(n×m + s×4) = O(n×m + s)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 1e8
using namespace std;


int main() {
    fast;
    int n, m, k, s, a[10][5], x; cin >> n >> m >> k >> s;
    memset(a, 243, sizeof(a));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> x;//每种类型在每个方向上的最大值
        a[x][0] = max(a[x][0], -i-j);//左上
        a[x][1] = max(a[x][1], -i+j);//右上
        a[x][2] = max(a[x][2], i-j);//左下
        a[x][3] = max(a[x][3], i+j);//右下
    }
    int ans = -inf;
    cin >> x;//读入序列的第一个元素
    for (int i = 2, y; i <= s; ++i) {//遍历序列的相邻元素对
        cin >> y;
        for (int j = 0; j <= 3; ++j) ans = max(ans, a[x][j]+a[y][3-j]);//x类型和y类型的组合值
        x = y;
    }
    cout << ans;
    return 0;
}