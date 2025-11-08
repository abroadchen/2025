//
// Created by Psy.C on 2025/10/29.
//
/*
*a, b, c, d：矩形区域参数
n：字母种类数
t：临时变量，用于读取每个字母的数量
x, y：当前位置坐标
dir：移动方向（1表示向下，-1表示向上）
 *
*a, b：第一个矩形的高和宽
c, d：第二个矩形的高和宽
*标记第一个矩形区域（从(1,1)到(a,b)）为有效区域：
用双重循环将g[1..a][1..b]设为true
*标记第二个矩形区域（从(a+1,1)到(a+c,d)）为有效区域：
用双重循环将g[a+1..a+c][1..d]设为true
这两个矩形是垂直排列的，上面一个a×b的矩形，下面一个c×d的矩形
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 110;
int a, b, c, d, n, t, x, y, dir;
bool g[N][N];//标记哪些格子是有效的填充区域
char ans[N][N];//存储最终结果（每个格子填入的字母）

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b >> c >> d >> n;

    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j)
            g[i][j] = 1;
    }
    for (int i = a + 1; i <= a + c; ++i) {
        for (int j = 1; j <= d; ++j)
            g[i][j] = 1;
    }
    if (b > d) {//如果上面矩形的宽度大于下面矩形的宽度
        if (d&1) x = a + c, y = 1, dir = -1;//如果下面矩形宽度为奇数：起始位置在左下角，方向向上
        else x = 1, y = 1, dir = 1;//如果下面矩形宽度为偶数：起始位置在左上角，方向向下
    } else if (b&1) x = 1, y = 1, dir = 1;//如果上面矩形宽度为奇数：起始位置在左上角，方向向下
    else x = a + c, y = 1, dir = -1;//否则：起始位置在左下角，方向向上

    for (int i = 0; i < n; ++i) {//循环处理每种字母
        cin >> t;//读取第i种字母需要填充的数量
        while (t--) {
            ans[x][y] = 'a' + i;//在当前位置填入对应字母
            x += dir;//按当前方向移动一行
            if (!g[x][y]) {//如果移动后的位置不是有效区域
                x -= dir;//回退一步，向右移动一列，改变方向
                y++;
                dir = -dir;
            }
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= max(b, d); ++i) {//按行输出结果，行数为两个矩形宽度的最大值
        for (int j = 1; j <= a + c; ++j)//对每一列
            cout << (g[j][i] ? ans[j][i] : '.');//如果是有效区域则输出填充的字母
        cout << endl;
    }
    return 0;
}