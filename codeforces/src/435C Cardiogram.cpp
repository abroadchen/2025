//
// Created by Psy.C on 2026/2/6.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    //输入序列 图形信息
    int a[1005]{}, b[2005][2005]{}, tot = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i], tot += a[i];
    int mx = 1000, mn = 1000;//y坐标的最大值 y坐标的最小值
    ///i = 1: 序列索引
    ///x = 0: 当前行坐标（垂直方向）
    ///y = 1000: 当前列坐标（水平方向），以1000为基准
    for (int i = 1, x = 0, y=1000; i <= n; ++i) {
        x++;//向下移动一行
        if (i&1) {
            a[i]--;//减少一个单位（因为当前点已标记）
            b[x][y] = 1;//在当前位置标记为1（代表'/'）
            while (a[i]--) {
                x++; y++;//同时向下行和右列移动
                b[x][y] = 1;
            }
            mx = max(mx, y);//更新最大y坐标
        } else {
            a[i]--;
            b[x][y] = 2;//在当前位置标记为2（代表"\\"）
            while (a[i]--) {
                x++; y--;
                b[x][y] = 2;
            }
            mn = min(mn, y);
        }
    }
    for (int i = mx; i >= mn; --i) {
        for (int j = 1; j <= tot; ++j) {//从1到总计数遍历每一行
            if (b[j][i] == 1) cout << '/';
            else if (b[j][i] == 2) cout << "\\";
            else cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}