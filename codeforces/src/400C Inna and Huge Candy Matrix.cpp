//
// Created by Psy.C on 2026/1/31.
//
/**
* n、m: 矩阵的尺寸
x、y、z: 操作次数
p: 查询点的数量
 *xi、yi用于存储当前点坐标，flag用于标记是否进行了旋转
 *
*执行x%4次90度顺时针旋转操作
旋转公式：(x,y) → (y, n+1-x)，但根据步数有特殊处理
保存原xi到临时变量t
如果是第2次旋转，特殊处理旋转公式；否则使用一般公式
 *
*如果x%4为1或3（意味着矩阵旋转了90°或270°），交换n和m的值
设置flag为1，标记发生了尺寸交换
 *
*执行y%2+1次关于水平中线的翻转操作
每次翻转：yi = m + 1 - yi（垂直翻转）
 *
 *计算反向旋转次数s = 4 - z%4，相当于逆时针旋转z次
*执行s次逆时针旋转操作
使用类似的旋转公式，但在第2和第4步有特殊处理
 *
 *输出变换后的坐标
 *如果之前交换了n和m，现在还原回来，并重置flag
 *
 *
*x次90度顺时针旋转
y次水平翻转
z次90度逆时针旋转
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m, x, y, z, p; cin >> n >> m >> x >> y >> z >> p;
    int xi, yi, flag = 0;
    while (p--) {
        cin >> xi >> yi;
        for (int i = 1; i <= x%4; ++i) {
            const ll t = xi;
            if (i == 2) xi = yi, yi = static_cast<int>(m + 1 - t);
            else xi = yi, yi = static_cast<int>(n + 1 - t);
        }
        if (x%4 == 1 || x%4 == 3) swap(n, m), flag = 1;
        for (int i = 0; i <= y%2+1; ++i) yi = m + 1 - yi;
        const int s = 4 - z%4;
        for (int i = 1; i <= s; ++i) {
            const ll t = xi;
            if (i == 2 || i == 4) xi = yi, yi = static_cast<int>(m + 1 - t);
            else xi = yi, yi = static_cast<int>(n + 1 - t);
        }
        cout << xi << ' ' << yi << '\n';
        if (flag) swap(n, m), flag = 0;
    }
    return 0;
}