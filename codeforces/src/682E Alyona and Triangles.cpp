//
// Created by Psy.C on 2026/4/15.
//
/**
operator-重载：实现两个点相减（向量减法），返回新的点
operator+重载：实现两个点相加（向量加法），返回新的点
operator*重载：实现叉积运算（向量叉积），返回long long类型结果
1ll*x*o.y - 1ll*y*o.x 是计算两个向量的叉积，用于计算三角形面积
p[N]：存储输入的n个点
A, B, C：最终输出的三个点

计算由点i, j, k构成的三角形的面积（实际是面积的2倍）
p[j] - p[i]：从点i到点j的向量
p[k] - p[i]：从点i到点k的向量
abs()：取绝对值，因为叉积可能是负数（取决于点的方向

n：输入点的数量
S：目标面积（实际上在后面被重新赋值为实际最大面积）
输入：读取点数n和目标面积S
循环：从1到n读取每个点的坐标(x,y)
初始化：a,b,c分别指向第1,2,3个点作为初始三角形
flag：循环控制标志
S：初始化为由前三个点组成的三角形面积

外层while循环：当找到更优解时继续循环
内层for循环：尝试用每个点替换当前三角形的顶点
三次面积比较：
尝试将c点替换为点i：area(a, b, i)
尝试将b点替换为点i：area(a, i, c)
尝试将a点替换为点i：area(i, b, c)
更新逻辑：如果找到更大的面积，更新S和相应的顶点，并设置flag=1继续循环

构造了以最大三角形为基础的平行四边形的另外三个顶点
从三角形的三个顶点(p[a], p[b], p[c])扩展出平行四边形的三个顶点(A, B, C)
本质上是找到一个点，使得这三个点和原三角形的某个点构成平行四边形
按顺序输出三个构造出的点的坐标
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5005;

struct node {
    int x, y;
    node operator-(const node &o) const { return {x - o.x, y - o.y}; }
    node operator+(const node &o) const { return {x + o.x, y + o.y}; }
    ll operator*(const node &o) const { return 1ll*x*o.y - 1ll*y*o.x; }
} p[N], A, B, C;

ll area(int i, int j, int k) {
    return abs((p[j] - p[i]) * (p[k] - p[i]));
}

int n;
ll S;
int main() {
    fast;
    cin >> n >> S;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    int a = 1, b = 2, c = 3; bool flag = 1; S = area(a, b, c);
    while (flag) {
        flag = 0;
        for (int i = 1; i <= n; ++i) {
            ll t = area(a, b, i);
            if (t > S) S = t, c = i, flag = 1;
            t = area(a, i, c);
            if (t > S) S = t, b = i, flag = 1;
            t = area(i, b, c);
            if (t > S) S = t, a = i, flag = 1;
        }
    }
    A = p[a] + (p[b] - p[c]), B = p[b] + (p[c] - p[a]), C = p[c] + (p[a] - p[b]);
    cout << A.x << ' ' << A.y << '\n' << B.x << ' ' << B.y << '\n' << C.x << ' ' << C.y << '\n';
    return 0;
}