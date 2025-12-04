//
// Created by Psy.C on 2025/12/4.
//
/*
*n, m：网格的行数和列数
k：查询次数
 *
*检查点(i,y)是否能成为离(x,y)更近的点：
x,y：查询点坐标
i：当前检查的行号
g,h：当前找到的最近点坐标
L：当前最小曼哈顿距离
 *
*距离更短，或者
距离相等但坐标字典序更小
根据flag值决定按(i,j)还是(j,i)的顺序比较
 */
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
using namespace std;

constexpr int inf = 0x7fffffff;
int n, m, k, u[N][N], d[N][N];
bool flag = false;//是否交换了行列

int find(int p[], const int x) { return x == p[x] ? x : p[x] = find(p, p[x]); }

void ok(const int x, const int y, const int i, int& g, int& h, int& L) {
    if (i < 1 || i > n) return;
    int j = find(u[i], y);//在第i行中，从位置y开始查找左侧最近的可用位置。
    if (j != 0) {//找到了有效的左侧位置
        const int t = abs(x - i) + abs(y - j);//当前点(x,y)到候选点(i,j)的曼哈顿距离
        if (t < L || t == L && (!flag && (i < g || i == g && j < h) ||
            flag && (j < h || j == h && i < g))) {
            L = t, g = i, h = j;
        }
    }
    j = find(d[i], y);//在第i行中，从位置y开始查找右侧最近的可用位置
    if (j != m + 1) {
        const int t = abs(x - i) + abs(y - j);
        if (t < L || t == L && (!flag && (i < g || i == g && j < h) ||
            flag && (j < h || j == h && i < g))) {
            L = t, g = i, h = j;
        }
    }
}

int main() {
    fast;
    cin>>n>>m>>k;
    if (n > m) { swap(n, m); flag = true; }
    for (int i = 1; i <= n; ++i) {//对于每一行，u[i][j]和d[i][j]初始都指向自己
        for (int j = 0; j <= m + 1; ++j) u[i][j] = d[i][j] = j;
    }
    while (k--) {
        int x, y; cin>>x>>y;
        if (flag) swap(x, y);//如果之前交换过行列，则现在也交换查询点坐标
        int g = -1, h = -1, L = inf;
        for (int i = 0; i <= L; ++i) {//只在距离不超过当前最优距离的范围内搜索
            ok(x, y, x - i, g, h, L);
            ok(x, y, x + i, g, h, L);
        }
        u[g][h] = h - 1; d[g][h] = h + 1;//标记点(g,h)已被占用
        if (flag) swap(g, h);//如果之前交换过行列，则输出前再交换回来
        cout << g << ' ' << h << '\n';
    }
    return 0;
}