//
// Created by Psy.C on 2026/2/5.
//
/**
* 第一个max：从(i,j)形成"十字"形状，分别从上下左右四个方向汇聚
ans[1][i-1][j]：从上方到达(i-1,j)的最大值
ans[4][i+1][j]：从下方到达(i+1,j)的最大值
ans[2][i][j-1]：从右边到达(i,j-1)的最大值
ans[3][i][j+1]：从左边到达(i,j+1)的最大值
第二个max：另一种交叉模式，形成"井字"形状的另一组合
mx = max(mx, ...)：记录找到的最大值
 *
*从左侧到达(i,j-1)的路径
从右侧到达(i,j+1)的路径
从下方到达(i+1,j)的路径
从上方到达(i-1,j)的路径
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int mp[N][N]{}, i, j;
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j)
        cin >> mp[i][j];
    int ans[5][N][N]{};//[方向][行][列]
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
        //当前位置可以从上方或左方到达
        ans[1][i][j] = max(ans[1][i-1][j], ans[1][i][j-1]);
        ans[1][i][j] += mp[i][j];//加上当前格子的值
    }
    for (i = n; i >= 1; --i) for (j = 1; j <= m; ++j) {
        //当前位置可以从下方或左方到达
        ans[2][i][j] = max(ans[2][i+1][j], ans[2][i][j-1]);
        ans[2][i][j] += mp[i][j];
    }
    for (i = 1; i <= n; ++i) for (j = m; j >= 1; --j) {
        //当前位置可以从上方或右方到达
        ans[3][i][j] = max(ans[3][i-1][j], ans[3][i][j+1]);
        ans[3][i][j] += mp[i][j];
    }
    for (i = n; i >= 1; --i) for (j = m; j >= 1; --j) {
        //当前位置可以从下方或右方到达
        ans[4][i][j] = max(ans[4][i+1][j], ans[4][i][j+1]);
        ans[4][i][j] += mp[i][j];
    }
    int mx = 0;
    //遍历除了边界的所有内部点(i,j)
    for (i = 2; i < n; ++i) for (j = 2; j < m; ++j) {
        mx = max(mx, ans[1][i-1][j] + ans[4][i+1][j] +
            ans[2][i][j-1] + ans[3][i][j+1]);
        mx = max(mx, ans[1][i][j-1] + ans[4][i][j+1] +
            ans[2][i+1][j] + ans[3][i-1][j]);
    }
    cout << mx;
    return 0;
}