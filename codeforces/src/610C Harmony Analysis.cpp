//
// Created by Psy.C on 2026/3/23.
//
/**
a[N][N]：存储图案的二维数组
q[]：存储2的幂次（2^0到2^9），用于控制每个阶段的大小
+ +
+ *
左上角：保持原样
右上角：复制左下角
左下角：复制右上角
右下角：翻转左上角（+变成*，*变成+）

时间复杂度：
O(4^n)，因为最终矩阵大小是2^n × 2^n。
空间复杂度：
O(4^n)，用于存储矩阵。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 666;

char a[N][N];
int q[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void build() {
    a[1][1] = '+', a[1][2] = '+', a[2][1] = '+', a[2][2] = '*';
    for (int k = 1; k < 9; ++k) {
        //复制左下角块到右上角块
        for (int i = 1+q[k]; i <= q[k+1]; ++i)
            for (int j = 1; j <= q[k]; ++j)
                a[i][j] = a[i-q[k]][j];
        //复制右上角块到左下角块
        for (int i = 1; i <= q[k]; ++i)
            for (int j = 1+q[k]; j <= q[k+1]; ++j)
                a[i][j] = a[i][j-q[k]];
        //处理右下角块，根据左上角块变换
        for (int i = 1+q[k]; i <= q[k+1]; ++i)
            for (int j = 1+q[k]; j <= q[k+1]; ++j) {
                if (a[i-q[k]][j-q[k]] == '+') a[i][j] = '*';
                if (a[i-q[k]][j-q[k]] == '*') a[i][j] = '+';
            }
    }
}

int n;
int main() {
    fast;
    cin >> n; build();
    if (n == 0) cout << "+\n";
    else {
        for (int i = 1; i <= q[n]; ++i) {
            for (int j = 1; j <= q[n]; ++j)
                cout << a[i][j];
            cout << '\n';
        }
    }
    return 0;
}