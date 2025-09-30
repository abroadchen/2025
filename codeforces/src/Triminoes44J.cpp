//
// Created by Psy.C on 2025/9/28.
//
/*
*s[N][N]: 原始输入网格
z[N][N]: 结果输出网格
 *
 */
#include <cstdio>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

const int N = 1020;
int n, m;
char s[N][N], z[N][N];

int main() {
    scanf("%d%d", &n, &m);//读取网格的行数n和列数m
    rep(i, n) scanf("%s", s[i] + 1);//读取n行字符串存储到s数组中（从索引1开始存储）

    rep(i, n) rep(j, m) z[i][j] = '.';//将结果网格z初始化为全'.'（表示空位）
    rep(i, n) rep(j, m) {
        if (s[i][j] == 'b') {//如果当前位置是'b'字符
            char c = 'a' + (i + j / 2 * 2) % 4;//确保生成0-3的值，对应字符'a'-'d'
            if (s[i - 1][j] == 'w' && s[i + 1][j] == 'w') {//检查垂直方向是否都是'w'字符（上下相邻）
                s[i - 1][j] = s[i + 1][j] = s[i][j] = '.';//如果是，将这三个位置的s数组标记为'.'（表示已处理）
                z[i - 1][j] = z[i + 1][j] = z[i][j] = c;
            } else if (s[i][j - 1] == 'w' && s[i][j + 1] == 'w') {//否则检查水平方向是否都是'w'字符（左右相邻）
                s[i][j - 1] = s[i][j + 1] = s[i][j] = '.';
                z[i][j - 1] = z[i][j + 1] = z[i][j] = c;//在结果中用相同字符标记
            }
        }
    }
    rep(i, n) rep(j, m) {
        if (s[i][j] == 'b' || s[i][j] == 'w')//如果还有未处理的'b'或'w'字符，说明无法完全覆盖
            return puts("NO"), 0;
    }
    puts("YES");
    rep(i, n) puts(z[i] + 1);//从索引1开始输出每行
    return 0;
}