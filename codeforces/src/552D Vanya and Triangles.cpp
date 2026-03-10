//
// Created by Psy.C on 2026/3/10.
//
/**
node：表示二维点(x,y)
node2：表示直线方程y=kx+b的参数k(斜率)和b(截距)
C(x,k) = x!/(k!(x-k)!)

枚举所有点对，计算每条直线的参数
如果x=0（垂直线），设k=1000（表示无穷大斜率），b=x坐标
否则计算斜率k=y/x和截距b

n个点中选3个点的总数（最大可能的三角形数）
统计重合的直线（相同斜率和截距）
cnt：当前相同直线的数量
当直线不同时：
z = (sqrt(1 + 8*cnt) + 1) / 2：计算这条直线上点的数量
num -= C(z, 3)：减去不能构成三角形的三点组合数
cnt = 1：重置计数器

O(n²log(n²))，主要是排序的时间复杂度

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define eps 1e-7
using namespace std;
constexpr int N = 2010;

struct node { double x, y; } p[N];
struct node2 { double k, b; } p2[N*N];

ll C(const int x, const int k) {
    int i, j; ll s = 1;
    for (i = x, j = 1; i > x - k; i--, j++)
        s *= i, s /= j;
    return s;
}

int n, i, j, k;
int main() {
    fast;
    cin >> n;
    for (i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
    sort(p, p + n, [](const node a, const node b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    double x, y;
    for (i = 0; i < n-1; ++i)
        for (j = i + 1; j < n; ++j) {
            x = (p[j].x - p[i].x), y = (p[j].y - p[i].y);
            if (x == 0) {
                p2[k].k = 1000.; p2[k].b = p[j].x;
            } else {
                p2[k].k = y/x; p2[k].b = p[i].y - p2[k].k*p[i].x;
            }
            k++;
        }
    sort(p2, p2 + k, [](const node2 a, const node2 b) {
        if (a.k == b.k) return a.b < b.b;
        return a.k < b.k;
    });
    int cnt = 1, z;
    ll num = C(n, 3);
    for (i = 0; i < k; ++i) {
        if (fabs(p2[i].k - p2[i+1].k) <= eps && fabs(p2[i].b - p2[i+1].b) <= eps)
            cnt++;
        else {
            z = (sqrt(1 + 8*cnt) + 1) / 2;
            num -= C(z, 3);
            cnt = 1;
        }
    }
    cout << num << '\n';
    return 0;
}