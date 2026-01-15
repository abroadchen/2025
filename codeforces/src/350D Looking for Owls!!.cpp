//
// Created by Psy.C on 2026/1/15.
//

#include <iostream>
#include <algorithm>
#include <map>
#include <ranges>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ip pair<int, ii>
#define N 2123
#define sqr(x) ((x)*(x))
using namespace std;

struct node {
    int x, y;
    void input() { cin >> x >> y; }
    explicit node(const int x=0, const int y=0) : x(x), y(y) {}
    //const表明该方法不修改对象状态
    [[nodiscard]] int len() const { return x * x + y * y; }//距离原点的平方长度
} c[N];
node operator+(const node a, const node b) {//两个节点的坐标相加
    return node(a.x + b.x, a.y + b.y);
}
node operator*(const int v, const node a) {//整数与节点相乘
    return node(a.x * v, a.y * v);
}
node operator-(const node a, const node b) {
    return -1 * b + a;
}
node operator/(const node a, const int v) {//节点各坐标分量除以整数
    return node(a.x / v, a.y / v);
}
int dis(const node a, const node b) { return (a - b).len(); }//两点间距离的平方

//获取直线的表示形式：截距和方向向量
ip get(node a, const node b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    if (dy == 0) return {a.y, {0, 0}};//水平线 返回截距为y值，方向向量为(0,0)
    if (dx == 0) return {a.x, {0, 1}};//垂直线
    if (dx < 0) { dx *= -1, dy *= -1; }//统一方向 确保方向向量的x分量非负
    const int d = __gcd(abs(dx), abs(dy)); dx /= d, dy /= d;//化简斜率
    int t = (a.y % dy + dy) % dy; t = a.x + (t - a.y) / dy * dx;//计算截距
    return {t, {dx, dy}};
}

map<ip, vector<ii>> mp;//存储每条直线上的区间端点
map<ip, vector<int>> ans;//存储每条直线上各段的计数值

//在直线s上查询位置v的计数值
int get(const ip& s, int v) {
    if (!mp.contains(s)) return 0;//直线不存在则返回0
    vector<ii>& u = mp[s];//直线s上的区间端点向量u
    //第一个大于(v,1)的位置，计算索引st
    const int st = static_cast<int>(ranges::upper_bound(u,
    make_pair(v,1)) - u.begin());
    return ans[s][st];//直线s上第st段的计数值
}

//计算两点连线的垂直平分线
ip f(const node a, const node b) {
    const auto mid = (a + b) / 2;
    auto d = a - b;
    swap(d.x, d.y), d.x *= -1;//计算垂直向量（逆时针旋转90度）
    return get(mid + d, mid - d);//以mid+d和mid-d为端点的直线表示（垂直平分线）
}


int main() {
    fast;
    int n, m; cin >> n >> m;//n(线段数)和m(圆数)
    node a, b;
    while (n--) {//读入n个线段，将其投影到对应直线上，并记录区间端点的差分标记
        //每次读入线段端点
        a.input(); b.input(); a = 2 * a, b = 2 * b;//将坐标扩大2倍避免浮点运算
        if (a.x != b.x) {//线段不是垂直的
            mp[get(a, b)].emplace_back(min(a.x, b.x), 1);//左端点+1
            mp[get(a, b)].emplace_back(max(a.x, b.x)+1, -1);//右端点后-1
        } else {
            mp[get(a, b)].emplace_back(min(a.y, b.y), 1);//下端点+1
            mp[get(a, b)].emplace_back(max(a.y, b.y)+1, -1);//上端点后-1
        }
    }
    //对每条直线进行扫描线处理，计算每个区间被多少个线段覆盖
    for (auto&[fst, snd] : mp) {
        ranges::sort(snd);//对端点排序
        vector<int>& t = ans[fst];//获取当前直线的计数向量t
        int x = 0; t.push_back(x);//初始计数为0
        for (const auto val: snd | views::values) {//遍历所有端点值
            x += val;//累积差分
            t.push_back(x);//存储前缀和
        }
    }
    int r[N];
    for (int i = 0; i < m; ++i) {//输入圆心和半径，都扩大两倍
        c[i].input(); cin >> r[i];
        c[i] = 2 * c[i]; r[i] <<= 1;
    }
    int res = 0;
    for (int i = 0; i < m; ++i) for (int j = i + 1; j < m; ++j) {//枚举所有圆对(i,j)
        if (r[i] == r[j] && dis(c[i], c[j]) > sqr(r[i] + r[j])) {//半径相同且不相交
            int mid;//两圆连心线的中点坐标
            //两圆圆心在同一水平线上，中点y坐标就是共同的y值
            if (c[i].y == c[j].y) mid = c[i].y; else {
                mid = (c[i].x + c[j].x) >> 1;//中点x坐标是两圆心x坐标的平均值
            }
            res += get(f(c[i], c[j]), mid);//查询垂直平分线上的覆盖数
        }
    }
    cout << res << '\n';
    return 0;
}