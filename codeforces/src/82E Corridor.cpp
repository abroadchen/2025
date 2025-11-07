//
// Created by Psy.C on 2025/11/7.
//
/*
*n 区间数量
h 高度参数
f 焦距参数
l[N]和r[N]分别存储区间的左右端点
ans 存储最终答案
 *
 *如果区间跨越0点（左端点为负，右端点为正），
 *则将该区间分割为两个区间：[l[i], 0]和[0, r[i]]，并将n增加1
 *
 *双重循环遍历所有区间对，如果两个区间的左端点都为负或右端点都为正，
 *则从ans中减去相应的calc函数计算结果
 *
 */
#include <cstdio>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

const int N = 1010;
int n, h, f, l[N], r[N];
double ans;

double calc(double x, double y) {
    if (x == 0 || y == 0) return 0;
    if (x < 0 || y < 0) x = -x, y = -y;
    if (y < x) swap(x, y);
    if (y * (f - h) > x * (f + h)) return x * (1. * (f + h)/(f - h) + 1) * h;
    double a = f * (y - x) / (y + x), z = x * (f + a) / (f - h);
    return ((y + z) * (h - a) + (x + z) * (h + a)) / 2;
}


int main() {
    scanf("%d%d%d", &n, &h, &f);
    rep(i,n) {
        scanf("%d%d", &l[i], &r[i]);
        if (l[i] < 0 && r[i] > 0) {
            r[i + 1] = r[i];
            r[i] = 0;
            l[++i] = 0;
            ++n;
        }
    }
    ans = 0;
    rep(i,n) ans += (r[i] - l[i]) * (1. * (f + h) / (f - h) + 1) * 2 * h;
    rep(i,n) rep(j,n) if (l[i] < 0 && l[j] < 0 || r[i] > 0 && r[j] > 0) {
        ans -= calc(l[i], l[j]) + calc(r[i], r[j]) -
            calc(l[i], r[j]) - calc(r[i], l[j]);
    }
    printf("%.9f\n", ans);
    return 0;
}