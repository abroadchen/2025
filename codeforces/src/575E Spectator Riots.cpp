//
// Created by Psy.C on 2026/3/14.
//
/**
N = 1e5: 最大坐标值
M = 8e5+5: 数组最大容量
x, y: 坐标
operator-: 重载减法，计算两点差向量
operator^: 重载异或运算符，实际计算叉积
norm(): 计算点的模长平方
operator<: 重载小于运算符，用于排序

Andrew's凸包算法
iter_swap: 将最小点移到开头
按极角排序，如果共线则按距离排序
Graham扫描算法构建凸包
如果三点共线或右转，则弹出栈顶
返回凸包大小
计算三角形外接圆半径的平方
s = 2*cross(a,b,c): 2倍三角形面积
公式：R² = (abc)²/(16S²) = (abc)²/s² (其中s=2S)
如果面积为0返回负无穷

n: 输入点数
cnt: 当前点数
c: 凸包大小
d: 最佳三角形起始位置
p[]: 所有点
ch[]: 凸包点
ans: 最大外接圆半径平方
为每个点(x,y)和半径v生成边界点
分别处理四个方向的边界点
如果超出边界，则在边界上生成两个点

计算凸包
断言至少有3个点
复制前3个点到后面（便于循环处理）
遍历凸包上所有连续的三个点
计算外接圆半径平方
找到最大值及对应位置

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
#define cross(x,y,z) (((y)-(x))^((z)-(x)))
#define I(x,y) p[cnt++]={x,y}
using namespace std;
constexpr int N = 1e5, M = 8e5+5;

struct node {
    int x, y;
    node(int x0=0, int y0=0) : x(x0), y(y0) {}
    node operator-(const node& o) const { return node(x - o.x, y - o.y); }
    ll operator^(const node& o) const { return 1ll*x*o.y - 1ll*y*o.x; }
    ll norm() const { return 1ll*x*x + 1ll*y*y; }
    bool operator<(const node &o) const { return x < o.x || (x == o.x && y < o.y); }
};

int get(int n, node *p, node *q) {
    node *ret = q;
    iter_swap(p, min_element(p, p + n));
    sort(p + 1, p + n, [p](const node a, const node b) {
        ll r = cross(*p, a, b);
        return r > 0 || (r == 0 && (a - *p).norm() < (b - *p).norm());
    });
    for (int i = 0; i < n; *ret++ = p[i++])
        for (; ret > q + 1 && cross(ret[-2], p[i], ret[-1]) >= 0; --ret) {}
    return *ret = *p, ret - q;
}

ld calc(const node a, const node b, const node c) {
    ll s = 2*cross(a, b, c);
    return s ? (ld)(a-b).norm()*(b-c).norm()*(c-a).norm()/((ld)s*s) : -INFINITY;
}

int n, cnt, c, d;
node p[M], ch[M];
int main() {
    fast;
    cin >> n;
    ld ans = 0., cur;
    for (int i = 0, x, y, v; i < n; ++i) {
        cin >> x >> y >> v;
        x >= v ? I(x-v, y) : (d=v-x, I(0, max(0, y-d)), I(0, min(N, y+d)));
        y >= v ? I(x, y-v) : (d=v-y, I(max(0, x-d), 0), I(min(N, x+d), 0));
        x <= N-v ? I(x+v, y) : (d=x+v-N, I(N, max(0, y-d)), I(N, min(N, y+d)));
        y <= N-v ? I(x, y+v) : (d=y+v-N, I(max(0, x-d), N), I(min(N, x+d), N));
    }
    c = get(cnt, p, ch), assert(c >= 3); copy_n(ch, 3, ch+c); d = -1;
    for (int i = 0; i < c; ++i) {
        if ((cur=calc(ch[i], ch[i+1], ch[i+2])) > ans)
            d = i, ans = cur;
    }
    assert(~d);
    cout << ch[d].x << ' ' << ch[d].y << '\n' << ch[d+1].x << ' ' << ch[d+1].y << '\n'
        << ch[d+2].x << ' ' << ch[d+2].y << '\n';
    return 0;
}