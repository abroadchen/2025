//
// Created by Psy.C on 2025/11/6.
//
/*
*变量说明：
n: 网格大小（n×n）
a, b, c: 定义正方形区域的参数
xs[N], ys[N]: 4个关键点的坐标
t: 初始时间/能量
ts[N]: 到每个关键点的剩余时间
ans: 存储路径字符串
 *
 *计算函数：返回1+2+3+...+x的和，即x(x+1)/2 这用于计算曼哈顿距离路径的累计代价
 *
 *检查从位置(x,y)是否能到达关键点(xs,ys)并继续到终点(n,n)：
*当前位置在关键点左下方
当前位置在关键点左上方
当前位置在关键点右下方
当前位置在关键点右上方
 *
 *检查当前位置(x,y)是否能满足所有4个关键点的约束条件
 *
*计算4个关键点的坐标：
i=0: (a,b)
i=1: (a,b+c-1)
i=2: (a+c-1,b)
i=3: (a+c-1,b+c-1)
 *这4个点构成一个正方形的4个顶点
 *初始化每个关键点的时间限制为t
 *
*从(1,1)开始，目标是到达(n,n)
贪心策略：优先向右(R)，其次向上(U)
对每个移动：
检查移动后是否仍能满足所有约束
如果能，执行移动并更新路径
如果不能，输出"Impossible"并退出
更新到新位置后，减少到达各关键点的剩余时间
 *
 *时间复杂度：O(n²)
 *
 */
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

typedef long long ll;
const int N = 4;
int n, a, b, c, xs[N], ys[N];
ll t, ts[N];
string ans;

ll calc(ll x) { return x * (x + 1) / 2; }

bool ok(int x, int y, int xs, int ys, ll ts) {
    ll d1 = abs(x - xs) + abs(y - ys), d2 = abs(n - xs) + abs(n - ys);
    if (x <= xs && y <= ys) return calc(d1) + calc(d2) <= ts;
    else if (x <= xs) return calc(d2) - calc(y - ys - 1) + calc(d1) - calc(y - ys) <= ts;
    else if (y <= ys) return calc(d2) - calc(x - xs - 1) + calc(d1) - calc(x - xs) <= ts;
    return calc(d2) - calc(d1 - 1) <= ts;
}

bool ok(int x, int y) {
    for (int i = 0; i < 4; ++i) if (!ok(x, y, xs[i], ys[i], ts[i])) return 0;
    return 1;
}

int main() {
    scanf("%d%lld%d%d%d", &n, &t, &a, &b, &c);
    for (int i = 0; i < 4; ++i) {
        xs[i] = a + (i / 2) * (c - 1);
        ys[i] = b + (i % 2) * (c - 1);
        ts[i] = t;
    }
    int x(1), y(1);
    while (!(x == n && y == n)) {
        if (x < n && ok(x + 1, y)) x++, ans += "R";
        else if (y < n && ok(x, y + 1)) y++, ans += "U";
        else return puts("Impossible"), 0;
        for (int i = 0; i < 4; ++i) ts[i] -= abs(x - xs[i]) + abs(y - ys[i]);
    }
    printf("%s\n", ans.c_str());
    return 0;
}