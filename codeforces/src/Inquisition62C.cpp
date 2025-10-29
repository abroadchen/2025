//
// Created by Psy.C on 2025/10/28.
//
/*
 *定义常量N(点数上限)、M(每个多边形点数+1)、K(每个多边形实际点数)
*n: 多边形数量
p[N][M]: 存储多边形顶点坐标，p[i][j]表示第i个多边形的第j个顶点
vec: 存储交点参数的向量
ch: 交点参数值
an[K]: 存储向量叉积结果
ans: 最终结果(总长度)
 *
*使用叉积判断点是否在多边形内部
g1和g2分别表示点在多边形所有边的左侧或右侧
 *
 *
*获取线段ab与其他多边形的交点
添加端点0和1
对交点参数排序
 *
 */
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
#define sz(x) ((int)(x).size())
using namespace std;

typedef pair<double, double> pdd;
const double eps = 1e-8;
const int N = 110, M = 4, K = 3;
int n;
pdd p[N][M];
vector<double> vec;
double ch, an[K], ans;
//计算两个二维向量的叉积
double vect(pdd a, pdd b) { return a.first * b.second - a.second * b.first; }
//判断线段ab和线段cd是否相交
bool inter(pdd a, pdd b, pdd c, pdd d) {
    pdd ca = {c.first - a.first, c.second - a.second},
    ba = {b.first - a.first, b.second - a.second},
    dc = {d.first - c.first, d.second - c.second};
    double zn = vect(ba, dc);//计算ba和dc的叉积
    if (abs(zn) < eps) return false;//如果接近0说明两线段平行，不相交
    ch = vect(ca, dc);//计算交点参数，判断交点是否在线段ab上
    ch /= zn;
    return (-eps < ch && ch < 1 + eps);
}
//计算线段ab与其他多边形的交点
void cut(pdd a, pdd b, int x) {
    rep(i,n) if (i != x) {//遍历除当前多边形外的所有多边形
        rep(j,3) {//遍历多边形的每条边，如果相交则将交点参数添加到vec中
            pdd c = p[i][j], d = p[i][j + 1];
            if (inter(c,d,a,b) && inter(a,b,c,d))
                vec.push_back(ch);
        }
    }
}
double sqr(double x) { return x * x; }
double dist(pdd a, pdd b) { return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second)); }
//判断点e是否在除第x个多边形外的其他多边形内部
bool inside(pdd e, int x) {
    rep(i,n) if (i != x) {//遍历其他多边形
        rep(j,3) {//计算点e与多边形各边构成的向量叉积
            pdd c = p[i][j], d = p[i][j + 1],
            dc = {d.first - c.first, d.second - c.second},
            ec = {e.first - c.first, e.second - c.second};
            an[j] = vect(dc, ec);
        }
        bool g1(1), g2(1);
        rep(j,3) {
            if (an[j] < eps) g1 = 0;
            if (an[j] > -eps) g2 = 0;
        }
        if (g1 || g2) return true;
    }
    return false;
}


void solve() {
    rep(i,n) rep(j,3) {//遍历每个多边形的每条边
        pdd a = p[i][j], b = p[i][j + 1];
        vec.clear();
        cut(a,b,i);
        vec.push_back(0.0); vec.push_back(1.0);
        sort(vec.begin(), vec.end());
        rep(k,sz(vec) - 1) {//计算相邻两个交点间的线段
            pdd c = {a.first + vec[k] * (b.first - a.first), a.second + vec[k] * (b.second - a.second)},
            d = {a.first + vec[k + 1] * (b.first - a.first), a.second + vec[k + 1] * (b.second - a.second)};
            if (dist(c,d) > eps) {//如果线段长度大于eps且中点不在其他多边形内部，则累加到结果中
                pdd e = {(c.first + d.first) / 2, (c.second + d.second) / 2};
                if (!inside(e, i)) ans += dist(c, d);
            }
        }
    }
    printf("%.7lf\n", ans);
}

int main() {

    scanf("%d", &n);
    rep(i,n) {
        rep(j,3) scanf("%lf%lf", &p[i][j].first, &p[i][j].second);
        p[i][3] = p[i][0];//设置最后一个点等于第一个点(构成闭合多边形)
    }
    solve();
    return 0;
}