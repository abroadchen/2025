//
// Created by Psy.C on 2026/9/21.
//
/**
遍历每个方向 i。
若 i 方向"激活"（r[i][3] 非零）：
检查自身：前 3 项任一为 1 → 立即 YES。
检查其他方向 j：若 r[j][dir[i][j]] 非零 → 立即 YES。
全部检查完无冲突 → NO。
dir[i][j] 的语义

dir[i][j] 是一个从方向 i 影响到方向 j 的"冲突列号映射"。具体：

对 4×4 矩阵，行 = 方向，列 0/1/2 = 三个转向类型，列 3 = 激活标记。

r[j][dir[i][j]] 的含义：方向 j 的、会被方向 i 影响到的那个转向类型是否为 1。如果方向 i 被激活，且方向 j 在那个特定转向类型上也有车（为 1），则两者冲突 → YES。

dir 的值域是 {0,1,2}，正好对应前三个转向列。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int r[4][4], dir[][4] = {
    {1, 0, 1, 2}, {2, 1, 0, 1}, {1, 2, 1, 0}, {0, 1, 2, 1}
};

int main() {
    fast;
    for (auto& i : r)
        for (int& j : i) cin >> j;
    for (int i = 0; i < 4; ++i) {
        if (r[i][3]) {
            if (r[i][0] == 1 || r[i][1] == 1 || r[i][2] == 1) {
                cout << "YES\n"; return 0;
            }
            for (int j = 0; j < 4; ++j) {
                if (r[j][dir[i][j]]) {
                    cout << "YES\n"; return 0;
                }
            }
        }
    }
    cout << "NO\n";
    return 0;
}