//
// Created by Psy.C on 2025/10/14.
//
// 0:原点 | 1:x轴正 | 2:第一象限
// 3:y轴正 | 4:第二象限 | 5:x轴负
// 6:第三象限 | 7:y轴负 | 8:第四象限
/*
 *
*判断向量o相对于当前向量的位置：
返回1表示在左侧
返回-1表示在右侧
返回0表示共线
 *
 *
 *
 *
 */
#include <ios>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll eps = 1e-8;//定义精度常量，用于浮点数比较

struct Point {
    ll x, y;
    //比较运算符重载
    bool operator==(const Point& o) const {//判断两点是否相等（考虑精度误差）
        return (abs(x - o.x) <= eps && abs(y - o.y) <= eps);
    }
    bool operator!=(const Point& o) const {
        return !(*this == o);
    }
    bool operator<(const Point& o) const {//用于点的排序（先按x坐标，再按y坐标）
        if (abs(x - o.x) <= eps) return y < o.y - eps;
        return x < o.x - eps;
    }
    bool operator>(const Point& o) const {//不会修改*this对象
        return !(*this < o || *this == o);
    }
    //算术运算符重载
    Point operator+(const Point& o) const { return {x + o.x, y + o.y}; }//向量加法
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }//向量减法
    Point operator-() const { return {-x, -y}; }//向量取反
    Point operator*(const ll k) const { return {k*x, k*y}; }//向量数乘
    Point operator/(const ll k) const { return {x/k, y/k}; }//向量数除
    ll operator*(const Point& o) const { return x * o.x + y * o.y; }//向量点积
    ll operator^(const Point& o) const { return x * o.y - y * o.x; }//向量叉积

    int toleft(const Point& o) const {
        const auto t = (*this) ^ o;
        return (t > eps) - (t < -eps);
    }
    ll len2() const { return (*this) * (*this); }//计算向量长度的平方
    ll dis2(const Point& o) const { return (o - (*this)).len2(); }//计算到另一点距离的平方

    int quad() const {//判断点所在的象限
        if (abs(x) <= eps && abs(y) <= eps) return 0;
        if (abs(y) <= eps) return x > eps ? 1 : 5;
        if (abs(x) <= eps) return y > eps ? 3 : 7;
        return y > eps ? (x > eps ? 2 : 4) : (x > eps ? 8 : 6);
    }
};

vector<Point> convexhull(vector<Point> p) {//Graham扫描法求凸包函数
    vector<Point> st;
    if (p.size() <= 2) return p;//如果点数少于等于2，直接返回
    sort(p.begin(), p.end());
    const auto check = [](const vector<Point>& st, const Point& u) {//检查是否需要从凸包中移除点
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };
    for (const Point& u : p) {//正向扫描构建凸包下半部分
        while (st.size() > 1 && check(st, u)) st.pop_back();//如果不满足凸包条件，移除栈顶点
        st.push_back(u);//将当前点加入凸包
    }
    int k = st.size(); p.pop_back(); reverse(p.begin(), p.end());
    for (const Point& u : p) {//反向扫描，构建凸包上半部分
        while (st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();//移除重复的起始点
    return st;//返回凸包点集
}


int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;//读取点的数量
    vector<Point> a(n);//声明点集
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;//读取所有点的坐标
    a = convexhull(a);
    n = (int)a.size();//更新点数为凸包点数
    ll ans(0);
    for (int i = 0; i < n; ++i) {//遍历凸包上的每条边
        //计算边的x和y方向长度
        ll dx = abs(a[i].x - a[(i + 1) % n].x), dy = abs(a[i].y - a[(i + 1) % n].y);
        ans += max(dx, dy);//累加切比雪夫距离（Chebyshev distance）作为边长
    }
    cout << ans + 4 << '\n';
    return 0;
}