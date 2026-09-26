//
// Created by Psy.C on 2026/9/25.
//
/**
n 行 m 列。
a[N][N]：存 'R'、'G'、'B' 三种字符的矩阵
如果行数不能被 3 整除 且 列数也不能被 3 整除，那么无论是水平切（需要 n 整除 3）还是竖直切（需要 m 整除 3）都不可能，直接 NO
三种颜色必须全都出现过，否则无法分成三个不同颜色块，直接 NO
只有 n%3==0 才可能水平切（n 需要被 3 整除，每块高度 n/3）。
第一块 [1, n/3] 行：要求整块每个格子都等于参考点 a[1][1]（即第一块颜色统一）。
第二块 [n/3+1, n/3*2] 行：要求整块每个格子都等于参考点 a[n/3+1][1]（第二块颜色统一）。
第三块 [n/3*2+1, n] 行：要求整块每个格子都等于参考点 a[n/3*2+1][1]（第三块颜色统一）。
全部满足则返回 true（水平切可行
与 h() 对称，只是按列切：
第一块列 [1, m/3]：参考点 a[1][1]。
第二块列 [m/3+1, m/3*2]：参考点 a[1][m/3+1]。
第三块列 [m/3*2+1, m]：参考点 a[1][m/3*2+1]。
每列块内颜色统一则返回 true（竖直切可行）
只要水平切或竖直切其中一种可行就输出 YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;

int n, m;
char a[N][N];
bool h() {
    if (n%3) return 0;
    for (int i = 1; i <= n/3; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] != a[1][1])
                return 0;
    for (int i = n/3+1; i <= n/3*2; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] != a[n/3+1][1])
                return 0;
    for (int i = n/3*2+1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] != a[n/3*2+1][1])
                return 0;
    return 1;
}
bool l() {
    if (m%3) return 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m/3; ++j)
            if (a[i][j] != a[1][1])
                return 0;
    for (int i = 1; i <= n; ++i)
        for (int j = m/3+1; j <= m/3*2; ++j)
            if (a[i][j] != a[1][m/3+1])
                return 0;
    for (int i = 1; i <= n; ++i)
        for (int j = m/3*2+1; j <= m; ++j)
            if (a[i][j] != a[1][m/3*2+1])
                return 0;
    return 1;
}

//标记三种颜色是否出现过（后续要求三种颜色都出现才能是 YES）
bool r, g, b;
int main() {
    fast;
    cin >> n >> m;
    if (n%3 && m%3) { cout << "NO"; return 0; }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];//读入每个格子，并标记该颜色是否存在
            if (a[i][j] == 'R') r = 1;
            else if (a[i][j] == 'G') g = 1;
            else if (a[i][j] == 'B') b = 1;
        }
    if (!r||!g||!b) { cout << "NO"; return 0; }
    if (h() || l()) { cout << "YES"; return 0; }
    cout << "NO";
    return 0;
}