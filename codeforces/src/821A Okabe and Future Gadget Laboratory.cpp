//
// Created by Psy.C on 2026/9/23.
//
/**
多组输入，读入 n×n 矩阵（1 基索引）
对每个位置 (i,j)：
若 a[i][j] == 1，直接跳过（视为满足条件）。这里隐含规则：值恰为 1 的位置不需要检查
否则，双循环枚举所有 (k, p)：
检查是否存在某一对 (k,p) 使 a[i][j] == a[i][k] + a[p][j]。
a[i][k] 是同行第 i 行的某个元素，a[p][j] 是同列第 j 列的某个元素。
只要找到一对满足，ok = 1
若某个非 1 元素找不到任何 (k,p) 分解，则该位置不满足，flg = 0，提前退出。
全部满足 → 输出 "Yes"，否则 "No"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 60;
int n, a[N][N];
int main() {
    fast;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) cin >> a[i][j];
        int flg = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (a[i][j] == 1) continue;
                int ok = 0;
                for (int k = 1; k <= n; ++k) {
                    for (int p = 1; p <= n; ++p) {
                        if (a[i][j] == a[i][k]+a[p][j]) {
                            ok = 1;
                            break;
                        }
                    }
                    if (ok) break;
                }
                if (!ok) { flg = 0; break; }
            }
            if (!flg) break;
        }
        if (flg) cout << "Yes\n"; else cout << "No\n";
    }
    return 0;
}