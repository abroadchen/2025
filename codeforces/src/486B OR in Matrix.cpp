//
// Created by Psy.C on 2026/2/17.
//
/**
r, c: 矩阵的行数和列数
b[N][N]: 输入矩阵B
k: 临时变量，用于循环计数
a[N][N]: 结果矩阵A（初始化为-1）

时间复杂度：O(r×c×(r+c))
空间复杂度：O(r×c)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;

int r, c, b[N][N], k, a[N][N];
int main() {
    fast;
    cin >> r >> c;
    memset(a, -1, sizeof(a));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) {
            cin >> b[i][j];
            if (!b[i][j]) {//如果B矩阵中某个位置是0，那么A矩阵中对应行或列必须至少有一个0，才能使该位置变为0
                for (k = 0; k < c; ++k) a[i][k] = 0;//第i行的所有元素设为0
                for (k = 0; k < r; ++k) a[k][j] = 0;//第j列的所有元素设为0
            }
        }
    int flag = 1;//假设存在解
    for (int i = 0; i < r && flag; ++i)
        for (int j = 0; j < c; ++j) if (b[i][j]) {//所有非零元素
            for (k = 0; k < c; ++k)
                if (a[i][k]) break;//第i行是否有非零元素
            if (k < c) continue;
            for (k = 0; k < r; ++k)
                if (a[k][j]) break;//第j列是否有非零元素
            if (k == r) { flag = 0; break; }
        }
    if (flag) {
        cout << "YES\n";
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                cout << -a[i][j] << " \n"[j==c-1];
    } else cout << "NO\n";
    return 0;
}