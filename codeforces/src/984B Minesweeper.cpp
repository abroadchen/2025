//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
d 是 8 个方向偏移（上、下、左、右及四个对角），用于遍历某格周围八格。
s 存棋盘字符
if (s[x][y] == '*') return true;：当前格是地雷就直接合法（地雷本身不需要校验）。
int g = isdigit(s[x][y]) ? s[x][y]-'0' : 0;：若当前格是数字字符（0-9），g 取该数字；否则（是 . 空格）g=0，即周围应有 0 颗雷。
for (auto &k : d) if (s[x+k[0]][y+k[1]] == '*') cnt++;：遍历 8 个方向，统计当前格周围八格中地雷 * 的个数 cnt。
return cnt == g;：只有当"周围实际地雷数 == 该格应显示的数字（或空格的 0）"时才合法。
注意：访问 s[x+k[0]][y+k[1]] 可能越界（棋盘边界格），但因为 s 是全局数组且初始全 0，越界处读到的也是非 *，不会误判成雷，所以边界情况也能正确工作
读入棋盘大小 n、m。
for (int i = 1; i <= n; i++) scanf("%s", s[i]+1);：逐行读入字符串到 s[i][1] 起的位置（下标从 1 开始，方便配合 8 方向遍历）。
双重循环遍历每个格子 (i, j)：
if (check(i, j)) continue;：该格合法就跳过。
return cout << "NO\n", 0;：只要有一个格子不合法，立即输出 NO 并结束程序。（注意 cout << ... , 0 是逗号表达式，整体作为 return 值 0）
若所有格子都合法，输出 YES
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 505;
int d[][2] = {
    {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
};
char s[N][N];
bool check(int x, int y) {
    if (s[x][y] == '*') return true;
    int cnt = 0, g = isdigit(s[x][y]) ? s[x][y] - '0' : 0;
    for (auto &k : d) if (s[x+k[0]][y+k[1]] == '*') cnt++;
    return cnt == g;
}

int n, m;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", s[i]+1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (check(i, j)) continue;
            return cout << "NO\n", 0;
        }
    cout << "YES\n";
    return 0;
}