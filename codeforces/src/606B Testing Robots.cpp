//
// Created by Psy.C on 2026/3/22.
//
/**
n, m: 网格的行数和列数
x, y: 当前位置坐标
res[N]: 结果数组，记录每步是否到达新位置
vis[M][M]: 访问标记数组
s[N]: 存储移动指令字符串
res[0]=1表示初始位置被访问
在访问数组中标记起始位置

遍历每个移动指令:
'U': 向上移动(行号减1)，如果在边界内且未访问过则标记
'D': 向下移动(行号加1)，如果在边界内且未访问过则标记
'R': 向右移动(列号加1)，如果在边界内且未访问过则标记
'L': 向左移动(列号减1)，如果在边界内且未访问过则标记
res[i+1] = 1表示第i+1步到达了新位置
vis[x][y] = 1标记当前位置已访问

计算总共访问的新位置数(sum)
输出每一步的结果(1表示到达新位置，0表示重复访问)
计算剩余未访问的格子数:
如果当前位置已被访问过，剩余格子数为n*m-sum
如果当前位置未被访问过(最后停在新位置)，剩余格子数为n*m-sum+1
算法时间复杂度为O(len)，其中len是指令串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 505;
int n, m, x, y, res[N], vis[M][M];
char s[N];
int main() {
    fast;
    cin >> n >> m >> x >> y;
    cin >> s; int len = strlen(s);
    res[0] = 1; vis[x][y] = 1;
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'U') {
            if (x > 1) {
                x--;
                if (!vis[x][y]) { res[i+1] = 1; vis[x][y] = 1; }
            }
        }
        if (s[i] == 'D') {
            if (x < n) {
                x++;
                if (!vis[x][y]) { res[i+1] = 1; vis[x][y] = 1; }
            }
        }
        if (s[i] == 'R') {
            if (y < m) {
                y++;
                if (!vis[x][y]) { res[i+1] = 1; vis[x][y] = 1; }
            }
        }
        if (s[i] == 'L') {
            if (y > 1) {
                y--;
                if (!vis[x][y]) { res[i+1] = 1; vis[x][y] = 1; }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < len; ++i) {
        cout << res[i] << ' ';
        sum += res[i];
    }
    if (vis[x][y]) cout << n*m-sum << '\n';
    else cout << n*m-sum+1 << '\n';
    return 0;
}