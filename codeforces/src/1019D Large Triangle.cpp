//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
inf = 1e18：无穷大，被用作"竖直直线的斜率"特殊标记
点结构体，p[i] 存第 i 个点的坐标
比较函数：按横坐标 x 升序排序
向量减法：返回 A - B 的向量 (A.x-B.x, A.y-B.y)
叉积（cross product）‍ A ^ B = A.x*B.y - A.y*B.x。叉积的绝对值等于两向量围成平行四边形面积（三角形面积的 2 倍）
计算三角形 (x,y,z) 面积的 2 倍：|(p[y]-p[x]) ^ (p[z]-p[x])|。
因为 |叉积| = 2 × 三角形面积，后面用 S 时也会把输入的 S 乘以 2（见 main），所以这里直接比较整数值。
node：存一条边的两个端点位置 x、y（在某个数组中的下标）和这条边对应的斜率 k。
q：所有边（点对）的集合。
cmp2：按斜率 k 升序排序
因为 calc 返回的是面积的 2 倍，所以把目标 S 也乘 2 对齐单位
所有点按 x 升序排序（p[1]...p[n]）。
初始化两个映射：
id[i]：按 x 排序后，位置 i 处的原始点下标。初始 id[i]=i。
pos[i]：某个顺序（见后）下位置 i 对应到排序数组中的位置。初始 pos[i]=i。
id 和 pos 是互逆的双向映射：维护点在"当前顺序数组"和"原始坐标"之间的对应，用于后面 O(1) 交换更新
对每一对点 (i, j)（i<j），计算斜率 k：
若横坐标相同（竖直线），斜率设为 inf（∞）特殊标记；
否则 k = (y_j - y_i)/(x_j - x_i)（浮点）。
把这条边记为 {pos[i], pos[j], k} 放入 q，记录的是当前 pos 下标。
也就是：q 里存了所有点对的（两个位置 + 斜率）
把所有边按斜率 k 升序排好。
这是算法的关键前提：按斜率排序后，用"旋转扫描"（类似 Andrew 凸包、斜率排序法的思想）‍，能保证某些几何单调性，使后面的二分可成立。
x、y 是这条边两端在排序位置数组中的位置，保证 x < y
在位置区间 [1, x-1]（即比 x 更靠左的点中）二分寻找一个点 id[m]，使得三角形 (id[m], id[x], id[y]) 的 2 倍面积恰为 S。
因为按 x 排序且斜率处理后有单调性，calc 在这个区间随 m 单调变化（见下方原理说明），所以可用二分。
若 calc > S 则向左（r=m-1），否则向右（l=m+1
同样在 [y+1, n]（比 y 更靠右的点）二分，方向相反
处理完这条边后，把这条边的两个端点在 pos 和 id 中交换位置。
这实际上是在按斜率顺序"旋转"所有点——因为边集按斜率排序，当处理到某条边时，它的两端在当前"横坐标排序"中的相对顺序会被调整，保证算法的单调性始终成立。
枚举完所有边对仍找不到答案 → 输出 No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int N = 2e3+10;
constexpr ll inf = 1e18;

struct Point{ ll x, y; } p[N];
int cmp(const Point& A, const Point& B) { return A.x < B.x; }
Point operator-(Point A, Point B) { return {A.x-B.x, A.y-B.y}; }
ll operator^(Point A, Point B) { return A.x*B.y - A.y*B.x; }
ll calc(int x, int y, int z) { return abs(p[y]-p[x]^p[z]-p[x]); }

struct node { int x, y; double k; };
vector<node> q;
int cmp2(const node& A, const node& B) { return A.k<B.k; }

int n, pos[N], id[N];
ll S;
int main() {
    fast;
    cin >> n >> S; S *= 2;
    rep(i,n) cin >> p[i].x >> p[i].y;
    sort(p+1, p+n+1, cmp);
    rep(i,n) pos[i] = id[i] = i;
    rep(i,n) for (int j = i+1; j <= n; j++) {
        double k;
        if (p[i].x == p[j].x) k = inf;
        else k = 1.*(p[j].y-p[i].y)/(p[j].x-p[i].x);
        q.push_back({pos[i], pos[j], k});
    }
    ranges::sort(q, cmp2);
    for (auto &i : q) {
        int x = pos[i.x], y = pos[i.y];
        if (x > y) swap(x, y);
        int l = 1, r = x - 1;
        while (r >= l) {
            int m = (l+r)>>1;
            if (calc(id[m], id[x], id[y]) == S) {
                cout << "Yes\n";
                cout << p[id[m]].x << ' ' << p[id[m]].y << '\n';
                cout << p[id[x]].x << ' ' << p[id[x]].y << '\n';
                cout << p[id[y]].x << ' ' << p[id[y]].y << '\n';
                return 0;
            }
            if (calc(id[m], id[x], id[y]) > S) l = m+1; else r = m-1;
        }
        l = y + 1, r = n;
        while (r >= l) {
            int m = (l+r)>>1;
            if (calc(id[m], id[x], id[y]) == S) {
                cout << "Yes\n";
                cout << p[id[m]].x << ' ' << p[id[m]].y << '\n';
                cout << p[id[x]].x << ' ' << p[id[x]].y << '\n';
                cout << p[id[y]].x << ' ' << p[id[y]].y << '\n';
                return 0;
            }
            if (calc(id[m], id[x], id[y]) > S) r = m-1; else l = m+1;
        }
        swap(pos[i.x], pos[i.y]);
        swap(id[x], id[y]);
    }
    cout << "No\n";
    return 0;
}