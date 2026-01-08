//
// Created by Psy.C on 2026/1/8.
//
/**
* a[N][N]：二维数组，大小为N×N，存储结果矩阵
t[N]：一维数组，用作辅助标记数组
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;


int main() {
    fast;
    int n, a[N][N], t[N]; cin >> n;
    if (!(n&1)) {
        if (n < 6) { cout << "-1\n"; return 0; }
        a[1][5] = a[1][6] = 1;
        a[2][1] = a[2][6] = 1;
        a[3][1] = a[3][2] = a[3][5] = 1;
        a[4][1] = a[4][2] = a[4][3] = 1;
        a[5][2] = a[5][4] = 1;
        a[6][3] = a[6][4] = a[6][5] = 1;
        t[2] = t[3] = t[4] = 1;
        for (int i = 7; i <= n; i += 2) {//处理偶数的奇数索引位置
            t[i] = 1; a[i][1] = 1, a[1][i+1] = 1, a[i+1][i] = 1;
            for (int j = 2; j < i; ++j) {
                if (t[j]) a[j][i] = 1, a[i+1][j] = 1;
                else a[j][i+1] = 1, a[i][j] = 1;
            }
        }
    } else {
        a[1][2] = a[2][3] = a[3][1] = 1; t[3] = 1;
        for (int i = 4; i <= n; i += 2) {
            t[i] = 1; a[i][1] = 1, a[1][i+1] = 1, a[i+1][i] = 1;
            for (int j = 2; j < i; ++j) {
                if (t[j]) a[j][i] = 1, a[i+1][j] = 1;
                else a[j][i+1] = 1, a[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cout << a[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}