//
// Created by Psy.C on 2026/3/16.
//
/**
三个矩形的尺寸和原始索引

数组 b 是C风格数组，索引从0开始
但在填充时，代码使用的是1-based索引（px=1, py=1）
这意味着 b[0] 行没有被使用，有效数据从 b[1] 开始
b[i]：指向 b[i][0] 的指针
b[i] + 1：指向 b[i][1] 的指针

时间复杂度：O(max²)，其中max是最长边
空间复杂度：O(max²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105;
struct node { int x, y, idx; } g[3];

char b[N][N];//输出矩阵
void get(int x1, int y1, int x2, int y2, char c) {//用字符c填充矩形区域
    for (int i = x1; i <= x2; ++i)
        for (int j = y1; j <= y2; ++j)
            b[i][j] = c;
}

int main() {
    fast;
    int mx = -1;
    for (int i = 0; i < 3; ++i) {
        cin >> g[i].x >> g[i].y; g[i].idx = i;
        if (g[i].x < g[i].y) swap(g[i].x, g[i].y);//确保x≥y（统一方向）
        mx = max(mx, g[i].x);//最大宽度作为最终正方形边长
    }
    //按面积从大到小排序
    sort(g, g + 3, [](node& l1, node& l2) {
        if (l1.x != l2.x) return l1.x > l2.x;//先按第一维降序
        return l1.y > l2.y;//再按第二维降序
    });
    //px,py:当前位置坐标，x,y:剩余空间
    int px = 1, py = 1, x = mx, y = mx;
    for (int i = 0; i < 3; ++i) {
        if (x == g[i].x) {//当前高度等于矩形高度
            get(px, py, mx, mx, 'A' + g[i].idx);//在当前区域填充
            py += g[i].y;//更新纵坐标
            y -= g[i].y;//减少剩余宽度
        } else if (x == g[i].y) {
            get(px, py, mx, mx, 'A' + g[i].idx);
            py += g[i].x;
            y -= g[i].x;
        } else if (y == g[i].x) {//当前宽度等于矩形高度
            get(px, py, mx, mx, 'A' + g[i].idx);
            px += g[i].y;
            x -= g[i].y;
        } else if (y == g[i].y) {
            get(px, py, mx, mx, 'A' + g[i].idx);
            px += g[i].x;
            x -= g[i].x;
        } else { cout << "-1\n"; return 0; }
    }
    if (x*y != 0) { cout << "-1\n"; return 0; }//还有剩余空间，说明失败
    cout << mx << '\n';
    for (int i = 1; i <= mx; ++i) cout << b[i] + 1 << '\n';//填充后的矩阵
    return 0;
}