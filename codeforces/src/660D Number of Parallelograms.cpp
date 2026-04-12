//
// Created by Psy.C on 2026/4/11.
//
/**
嵌套循环考虑所有唯一的点对
计算点之间的坐标差值
计算连接它们的线段的斜率k和长度l
将此信息存储在映射中，为相似线段增加计数
对于每个相似线段组的计数，使用get()函数添加组合计数
除以2，因为在过程中每个线段对被计算了两次

 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2005;

struct node { int x, y; } p[N];
double get(int x, int y) {
    if (x == 0) return 1;
    return (double)y/(double)x;
}
int get(int n) {//n*(n-1)/2，表示从n个项目中取2个的组合数
    int sum = 0;
    for (int i = 1; i < n; ++i) sum += i;
    return sum;
}

struct lines {
    double len, k;
    bool operator<(const lines &o) const {
        if (k == o.k) return len < o.len;
        return k < o.k;
    }
};

double get(int x1, int y1, int x2, int y2) {
    double x = abs(x1 - x2); x = x*x;
    double y = abs(y1 - y2); y = y*y;
    return sqrt(x + y);
}

int n;
map<lines, int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j) {
            int x = p[i].x - p[j].x, y = p[i].y - p[j].y;
            double k = get(x, y), l = get(p[i].x, p[i].y, p[j].x, p[j].y);
            lines q{}; q.k = k, q.len = l; mp[q]++;
        }
    int ans = 0;
    for (auto &val: mp | views::values) ans += get(val);
    cout << ans/2 << '\n';
    return 0;
}