//
// Created by Psy.C on 2025/9/18.
//
/*
 *
*四重循环枚举所有可能的矩形：

length: 矩形的行数（高度）
width: 矩形的列数（宽度）
srow: 矩形起始行坐标
scol: 矩形起始列坐标
边界检查：

if (srow + length > n) continue;: 确保矩形不超出下边界
if (scol + width > m) continue;: 确保矩形不超出右边界

 *
 *
 *
 *
 *
 *时间复杂度：O(n³m³) - 四重循环枚举矩形 × 二重循环验证 空间复杂度：O(nm) - 存储网格数据
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<string> rv(n);
    for (int i = 0; i < n; ++i) cin >> rv[i];

    int maxPerim(0);
    for (int length = 1; length <= n; ++length)
        for (int width = 1; width <= m; ++width)
            for (int srow = 0; srow < n; ++srow) {
                if (srow + length > n) continue;
                for (int scol = 0; scol < m; ++scol) {
                    if (scol + width > m) continue;

                    bool possible(true);
                    for (int row = 0; row < length; ++row) {
                        if (!possible) break;
                        for (int col = 0; col < width; ++col) {
                            if (rv[srow + row][scol + col] == '1') {
                                possible = false;
                                break;
                            }
                        }
                    }
                    if (possible) {
                        int perim = 2 * (length + width);
                        maxPerim = (maxPerim > perim) ? maxPerim : perim;
                    }
                }
            }

    printf("%d\n", maxPerim);
    return 0;
}