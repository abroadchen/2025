//
// Created by Psy.C on 2025/11/16.
//
/*
*x, y：坐标
i：原始索引
t：象限标记
 *
*第一象限(x≥0,y≥0)：保持不变，标记t=1
第二象限(x<0,y>0)：镜像到第一象限，标记t=2
第四象限(x>0,y<0)：镜像到第一象限，标记t=3
第三象限(x<0,y<0)：镜像到第一象限，标记t=4
 *
*按x坐标排序所有点
mn：最小距离平方
s：维护当前扫描线附近的点的集合
初始化：将第一个点加入集合
*扫描线算法核心：
d：当前最小距离
移除距离当前点过远的点（x坐标差大于d）
*在y坐标范围内查找候选点：
l：y坐标≥(当前点y-d)的第一个点
r：y坐标≥(当前点y+d)的第一个点
检查范围内的所有点，更新最近点对
 *将当前点加入扫描线集合
 *
*输出最近点对的信息
关键处理：根据象限标记输出原始点的位置
 *
*时间复杂度：O(n log n)
空间复杂度：O(n)
 *
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;
typedef long double ld;
const ld eps = 1e-9;
const ll inf = 1e18+10;

int sgn(double x) { return (x > eps) - (x < -eps); }//判断浮点数的符号
struct node {
    ld x, y;
    int i = 0, t = 0;
    node() { x = 0; y = 0; }
    node(double x, double y, int i, int t) : x(x), y(y), i(i), t(t) {}
    node(const node& p) : x(p.x), y(p.y), i(p.i), t(p.t) {}
    bool operator==(node a) const { return sgn(a.x - x) == 0 && sgn(a.y - y) == 0; }
    bool operator!=(node a) const { return !(*this == a); }
    bool operator<(node a) const { return sgn(a.x - x) == 0 ? y < a.y : x < a.x; }
};

struct cmp {//按x坐标排序，x相同时按y坐标排序
    bool operator()(const node& a, const node& b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

ld dist(node a, node b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    vector<node> v;
    for (int i = 0, x, y; i < n; ++i) {
        cin>>x>>y;
        if (x >= 0 && y >= 0) v.push_back(node(x, y, i + 1, 1));
        else if (x < 0 && y > 0) v.push_back(node(-x, y, i + 1, 2));
        else if (x > 0 && y < 0) v.push_back(node(x, -y, i + 1, 3));
        else v.push_back(node(-x, -y, i + 1, 4));
    }
    sort(v.begin(), v.end(), cmp());
    ld mn = inf; set<node> s;
    s.insert(node(v[0].y, v[0].x, v[0].i, v[0].t));
    pair<node,node> ans; int j = 0;
    for (int i = 1; i < v.size(); ++i) {
        ld d = sqrt(mn);
        while (j < i && v[j].x < v[i].x - d) {
            s.erase(node(v[j].y, v[j].x, v[j].i, v[j].t));
            j++;
        }
        auto l = s.lower_bound(node(v[i].y - d, 0, 0, 0)),
        r = s.lower_bound(node(v[i].y + d, 0, 0, 0));
        for (auto it = l; it != r; ++it) {
            d = dist(v[i], node(it->y, it->x, it->i, it->t));
            if (d < mn) {
                mn = d;
                ans = {v[i], node(it->y, it->x, it->i, it->t)};
            }
        }
        s.insert(node(v[i].y, v[i].x, v[i].i, v[i].t));
    }
    cout << ans.first.i << " ";
    if (ans.first.t == 1) cout << 4;
    else if (ans.first.t == 4) cout << 1;
    else if (ans.first.t == 2) cout << 3;
    else cout << 2;
    cout << " " << ans.second.i << " " << ans.second.t << '\n';
    return 0;
}