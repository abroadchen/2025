//
// Created by Psy.C on 2026/1/28.
//
/**
*  #
 ###
   #
具体检查条件：

(i,j)：顶部的 #
(i+1,j)：中心的 #
(i+2,j)：底部的 #
(i+1,j-1)：中心左侧的 #
(i+1,j+1)：中心右侧的 #

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int vis[N][N]={};
    char a[N][N];//输入的字符矩阵
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        cin >> a[i][j];
    }
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '#' && !vis[i][j]) {//未访问过的 '#'
                //太靠近底部或左右边缘
                if (i >= n - 2 || j == 0 || j == n - 1) { flag = 1; break; }
                if (a[i+1][j] == '#' && !vis[i+1][j] && a[i+2][j] == '#' &&
                    !vis[i+2][j] && a[i+1][j-1] == '#' && !vis[i+1][j-1] &&
                    a[i+1][j+1] == '#' && !vis[i+1][j+1]) {
                    vis[i][j] = 1; vis[i+1][j] = 1;
                    vis[i+1][j-1] = 1; vis[i+1][j+1] = 1;
                    vis[i+2][j] = 1;
                } else { flag = 1; break; }
            }
        }
        if (flag) break;
    }
    if (flag) cout << "NO" << '\n';
    if (!flag) cout << "YES" << '\n';
    return 0;
}