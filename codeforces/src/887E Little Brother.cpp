//
// Created by Psy.C on 2026/10/8.
//
/**
定义了二维点与向量运算，| 点积、^ 叉积，dis 欧氏距离。sgn 带 eps 的符号判断
c 是线段 ab 的中点；k 是 ab 的法向单位向量（旋转 90°）。
之后所有考察点都在直线 c + k*t 上（过中点、沿法向），t 为参数
两个函数都是在参数轴上做约 80 次二分，找一个"不等式刚好成立/翻转"的临界参数 mid。o = c + k*mid 是直线上的候选点。
每次二分比较
d
i
s
(
p
,
o
)
−
R
dis(p,o)−R 与
d
i
s
(
a
,
o
)
dis(a,o) 的大小，依据 flg 选择收缩方向。
本质：对于直线上的点
o
o，判断它相对圆（圆心 p、半径 R）与点 a 的"到谁更近/差多少"的边界位置——用于把每个圆在参数轴上映射成一段区间 [find, find2]
对每个圆，用二分得到它在参数轴上覆盖的区间（用 +1/-1 差分事件表示区间进入/离开）。
排序后做扫描线：sum 记录当前被区间覆盖的圆数量。当 sum==0 时，说明直线 c+k*t 上这个位置不落在任何圆内——这是候选位置。
沿扫描线不断更新 ans 为"覆盖数为 0 的所有位置里，参数绝对值最小者"。
最终 o = c + k*ans，输出 dis(a,o)（a 到 o 的距离）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define pi acos(-1)
#define eps 1e-8
#define inf 1e12
using namespace std;
constexpr int N = 1e5+10;

int sgn(db x) { return x < eps ? (-x < eps ? 0 : -1) : 1; }

struct pt {
    db x, y;
    pt operator+(const pt& o) const { return {.x = x+o.x, .y = y+o.y}; }
    pt operator-(const pt& o) const { return {.x = x-o.x, .y = y-o.y}; }
    pt operator*(const db& o) const { return {.x = x*o, .y = y*o}; }
    pt operator/(const db& o) const { return {.x = x/o, .y = y/o}; }
    db operator|(const pt& o) const { return (x*o.x)+(y*o.y); }
    db operator^(const pt& o) const { return (x*o.y)-(y*o.x); }
};
db dis(pt A, pt B) { return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }

struct seq { db x; int op; } q[N<<1];

pt c, k, a;
db R;
db find(pt p, bool flg) {
    db l = -inf, r = inf;
    for (int i = 1; i <= 80; ++i) {
        db mid = (l+r)/2.000;
        pt o = c + (k*mid);
        if ((dis(p, o) - R > dis(a, o))^flg) l = mid;
        else r = mid;
    }
    return l;
}

db find2(pt p, bool flg) {
    db l = -inf, r = inf;
    for (int i = 1; i <= 80; ++i) {
        db mid = (l+r)/2.000;
        pt o = c + (k*mid);
        if ((dis(a, o) - dis(p, o) > R)^flg) r = mid;
        else l = mid;
    }
    return r;
}

pt b, p;
int cnt;
db ans = inf;
int main() {
    fast;
    cin >> a.x >> a.y >> b.x >> b.y;
    c = (a+b)/2.000; k = (b-a)/dis(a,b); k = {.x = -k.y, .y = k.x};
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p.x >> p.y >> R;
        bool flg = ((p-a)^(b-p)) > 0;//p 在 ab 的哪一侧
        q[++cnt] = {.x = find(p, flg), .op = flg?-1:1};//区间左端点（+1/-1 计数）
        q[++cnt] = {.x = find2(p,flg), .op = flg?1:-1};//区间右端点
    }
    //插入三个哨兵：0、-inf、inf
    q[++cnt] = {.x = 0, .op = 0}; q[++cnt] = {.x = -inf, .op = 0}; q[++cnt] = {.x = inf, .op = 0};
    sort(q+1, q+1+cnt, [](seq A, seq B) { return A.x < B.x; });
    int sum = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (!sum) ans = min(ans, fabs(q[i].x));//覆盖数为0的位置
        sum += q[i].op;
        if (!sum) ans = min(ans, fabs(q[i].x));
    }
    pt o = c + (k*ans);
    printf("%.10lf\n", dis(a, o));
    return 0;
}