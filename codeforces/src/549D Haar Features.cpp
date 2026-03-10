//
// Created by Psy.C on 2026/3/9.
//
/**
n, m：矩阵的行数和列数
ed[N][N]：目标矩阵（-1表示'B'，1表示'W'）
x[N][N]：当前状态矩阵
c：临时字符变量

ans：操作次数计数器
从右下角开始遍历矩阵（i=n到1，j=m到1）
d = ed[i][j] - x[i][j]：当前位置需要的变化量
如果当前位置不匹配目标状态：
执行操作：对左上角区域[1,1]到[i,j]的所有元素加上变化量d
ans++：操作次数加1

O(n²m²)：最坏情况下每个位置都可能触发O(nm)的操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int n, m, ed[N][N], x[N][N];
char c;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> c;
            ed[i][j] = c == 'B' ? -1 : 1;//将字符转换为数字：'B'→-1，'W'→1
        }
    int ans = 0;
    for (int i = n; i >= 1; --i)
        for (int j = m, d; j >= 1; --j) {
            d = ed[i][j] - x[i][j];
            if (x[i][j] != ed[i][j]) {
                for (int u = 1; u <= i; ++u)
                    for (int v = 1; v <= j; ++v)
                        x[u][v] += d;
                ans++;
            }
        }
    cout << ans << '\n';
    return 0;
}