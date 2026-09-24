//
// Created by Psy.C on 2026/9/23.
//
/**
读入棋盘。
若 'X' 总数少于 4，直接输出 NO 并结束（不满足"已下至少 4 个 X"的前提）。
枚举每个**空白格 '.'**作为"下一步落子位置"。
在每个位置，检查 8 个方向（横、竖、两条对角线）上，从该位置沿方向延伸的第 1、2、3、4 格（即 i1..j4）——注意不含当前位置本身（位置用 . 占位）。
统计这 4 个格子中 'X' 的个数 n 和 '.' 的个数 m。
若满足 m == 1 && n == 3，即这 4 个格子里恰好 3 个是 X、1 个是空白，那么在当前格落一个 X 后：
加上当前位置 → 形成 5 个连续 X（五连）‍。
输出 YES，结束。
若遍历完所有空白格和方向都没有满足条件，输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char c[11][11];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int get() {
    int s = 0;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            s += c[i][j] == 'X';
    return s;//棋盘上 'X' 的总个数
}

int n, m;
int main() {
    fast;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) cin >> c[i][j];
    if (get() < 4) { cout << "NO"; return 0; }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (c[i][j] - 'X') continue;
            for (int k = 0; k < 8; ++k) {
                int A = dx[k], B = dy[k], i1 = i+A, j1 = j+B,
                i2 = i1+A, j2 = j1+B, i3 = i2+A, j3 = j2+B, i4 = i3+A, j4 = j3+B;
                if (i1 < 0 || i1 > 9 || i2 < 0 || i2 > 9 || i3 < 0 || i3 > 9 || i4 < 0 || i4 > 9 ||
                    j1 < 0 || j1 > 9 || j2 < 0 || j2 > 9 || j3 < 0 || j3 > 9 || j4 < 0 || j4 > 9)
                    continue;
                n = (c[i1][j1] == 'X') + (c[i2][j2] == 'X') + (c[i3][j3] == 'X') + (c[i4][j4] == 'X');
                m = (c[i1][j1] == '.') + (c[i2][j2] == '.') + (c[i3][j3] == '.') + (c[i4][j4] == '.');
                if (m == 1 && n == 3) { cout << "YES"; return 0; }
            }
        }
    }
    cout << "NO";
    return 0;
}