//
// Created by Psy.C on 2026/4/20.
//
/**
num从1开始填充，r表示当前行（从第0行开始），c表示当前列（从中间列开始）
当填入数字不超过n²时循环执行
在位置(r,c)填入当前数字num，然后num自增
计算下一个位置：向上一行（r-1），向右一列（c+1）
使用模运算确保索引在有效范围内（0到n-1之间）
如果计算出的下一个位置为空（值为0），则移动到该位置
如果不为空，则向下移动一行（保持当前列不变）
循环结束后，按行输出整个二维数组
每个数字后加空格，每行结束后换行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

void get(int n) {
    vector a(n, vector(n, 0));
    int num = 1, r = 0, c = n/2;
    while (num <= n*n) {
        a[r][c] = num; num++;
        int nr = (r - 1 + n) % n, nc = (c + 1) % n;
        if (a[nr][nc] == 0) { r = nr, c = nc; }
        else r = (r + 1) % n;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
}

int n;
int main() {
    fast;
    cin >> n; get(n);
    return 0;
}