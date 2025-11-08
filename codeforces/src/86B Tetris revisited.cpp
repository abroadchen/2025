//
// Created by Psy.C on 2025/11/7.
//
/*
 *上(-1,0)、左(0,-1)、右(0,1)、下(1,0)
 *
 *" %s"用于跳过前导空白字符
*检查当前位置(i,j)和右边位置(i,j+1)是否都是'.'
如果是，则将这两个相邻的点填充为相同的数字字符
'0' + (3*i+j) % 10: 生成0-9的数字字符，确保不同的位置对有不同的数字
*检查当前位置(i,j)和下方位置(i+1,j)是否都是'.'
如果是，则将这两个相邻的点填充为相同的数字字符
 *
 */
#include <cstdio>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;

const int N = 1010;
char t[N][N];
int dx[] = {-1,0,0,1}, dy[] = {0,-1,1,0};

int main() {
    int h, w;
    while (scanf("%d%d", &h, &w) == 2) {
        rep(i,h) scanf(" %s", t[i]);
        rep(i,h) rep(j,w-1) if (t[i][j]=='.' && t[i][j+1]=='.') {
            t[i][j] = t[i][j+1] = '0' + (3*i+j) % 10;
        }
        rep(j,w) rep(i,h-1) if (t[i][j]=='.' && t[i+1][j]=='.') {
            t[i][j] = t[i+1][j] = '0' + (3*i+j) % 10;
        }
        bool flag(1);
        rep(i,h) rep(j,w) if (t[i][j]=='.') {
            char s = '@';//表示未找到有效邻居
            rep(k,4) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < h && y >= 0 && y < w && t[x][y] != '#') {
                    s = t[x][y];//设为该邻居的字符
                }
            }
            if (s == '@') flag = 0;//没有找到有效邻居
            t[i][j] = s;//将当前位置填充为找到的字符
        }
        if (!flag) printf("-1\n");
        else {
            rep(i,h) printf("%s\n", t[i]);
        }
    }
    return 0;
}