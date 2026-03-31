//
// Created by Psy.C on 2026/3/31.
//
/**
p：价值/收益
t：时间/成本
tl, tr：时间区间
w：比率 p/t
n：元素数量
T：总时间

检查参数 c 是否满足约束条件
遍历每个元素，维护当前最大值 mx
当 s[u].p 与 s[i].p 不同时，更新 mx
检查当前元素的值是否小于等于 mx

读入每个元素的价值 p
读入每个元素的时间 t，累加得到总时间 T
计算比率 w = p/t
按照 p/t 比率降序排序
计算时间区间：
tl：该组元素之前的累计时间
tr：该组元素的结束时间
按照 p 值升序排序
在 [0,1] 范围内二分搜索满足条件的最大 c
时间复杂度：O(n log n + n log(1/ε))，主要来自排序和二分搜索
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-12
using namespace std;
constexpr int N = 2e5+5, inf = 1e9;

struct node { double p, t, tl, tr, w; } s[N];

int n;
double T;
bool ok(double c) {
    int u = 0;
    double mx = -inf;
    for (int i = 1; i <= n; ++i) {
        while (u + 1 < i && abs(s[u+1].p - s[i].p) > eps) {
            u++;
            mx = max(mx, s[u].p*(1-c*(s[u].tl+s[u].t)/T));
        }
        double w = s[i].p*(1-c*s[i].tr/T);
        if (abs(mx - w) > eps && mx > w) return false;
    }
    return true;
}

bool vis[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i].p;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i].t; T += s[i].t;
        s[i].w = s[i].p/s[i].t;
    }
    sort(s + 1, s + n + 1, [](const node &x, const node &y) {
        return x.w > y.w;
    });
    int u = 0; double T0 = 0;
    for (int i = 1; i <= n; ++i) vis[i] = false;
    for (int i = 1; i <= n; ++i) {
        while (u + 1 < i && abs(s[u+1].p/s[u+1].t-s[i].p/s[i].t) > eps) {
            u++;
            T0 += s[u].t;
        }
        if (i == n || abs(s[i].p/s[i].t-s[i+1].p/s[i+1].t) > eps) {
            double T1 = T0;
            for (int j = u+1; j <= i; ++j) T1 += s[j].t;
            for (int j = u+1; j <= i; ++j)
                s[j].tl = T0, s[j].tr = T1;
        }
    }
    sort(s + 1, s + n + 1, [](const node &x, const node &y) {
        return x.p < y.p;
    });
    double l = 0, r = 1;
    while (l + eps < r) {
        double mid = (l + r) / 2;
        if (ok(mid)) l = mid; else r = mid;
    }
    printf("%.7f\n", l);
    return 0;
}