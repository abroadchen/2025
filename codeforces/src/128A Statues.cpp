//
// Created by Psy.C on 2025/11/18.
//
/*
*双重循环遍历9个方向：(-1,-1), (-1,0), (-1,1), (0,-1),
*(0,0), (0,1), (1,-1), (1,0), (1,1)
即当前点的周围8个相邻位置加上自身位置
 *
 *检查当前位置是否被'S'阻挡：如果第v列在第(u-k)行有'S'，则不能移动到(u,v)
 *检查当前位置上方是否被'S'阻挡：如果第v列在第(u-k-1)行有'S'，则不能移动到(u,v)
 *
 *
 */
#include <iostream>
using namespace std;

string s[8];

void dfs(int x, int y, int k) {
    if (k >= 7) { cout << "WIN"; exit(0); }
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int u = x + i, v = y + j;//计算新位置坐标(u,v)
            if (u < 0 || v > 7 || v < 0 || u > 7) continue;
            if (u - k >= 0 && s[u - k][v] == 'S') continue;
            if (u - k >= 1 && s[u - k - 1][v] == 'S') continue;
            dfs(u, v, k + 1);//递归调用dfs，在新位置进行下一步搜索，步数加1
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 0; i < 8; ++i) cin >> s[i];
    dfs(7, 0, 0);
    cout << "LOSE";
    return 0;
}