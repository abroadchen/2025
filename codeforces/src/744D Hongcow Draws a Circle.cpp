//
// Created by Psy.C on 2026/5/9.
//

#include <ranges>
#include <bits/stdc++.h>
#define ld long double
#define eps 1e-12
#define pi acos(-1.)
using namespace std;
constexpr int N = 1007, inf = 1e4;

struct node {
    ld x, y;
    node operator+(const node& o) const { return {x+o.x, y+o.y}; }
    node operator-(const node& o) const { return {x-o.x, y-o.y}; }
    ld operator*(const node& o) const { return x*o.y-y*o.x; }
    node operator*(const ld& o) const { return {x*o, y*o}; }
} p[N<<1];

struct node2 {
    ld x; int k;///x为角度值，k为事件类型（+1/-1/±inf）
    bool operator<(const node2& o) const { return x < o.x; }
} q[N<<3];

ld dis(node a, node b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
///弦对应的圆心角的一半
ld get(node a, node b, ld R) {
    ld d = dis(a, b)/2;
    return acos(d/R);
}
///tot为事件总数，n为一类点的数量，m为另一类点的数量
int tot, n, m;
bool check(int x, ld R) {///以点x为中心，半径为R的圆是否满足条件
    int i; tot = 0;
    //第一类点，添加全角度区间
    if (x <= n) q[++tot] = {-pi, 1}, q[++tot] = {pi, -1};
    else {
        for (i = 1; i <= n; i++) {//遍历第一类点
            if (dis(p[i], p[x]) > R + R - eps) continue;//距离太远
            //角度范围
            ld a = get(p[x], p[i], R), b = atan2(p[i].y-p[x].y, p[i].x-p[x].x), c = b-a, d = b+a;
            if (c < -pi) c += 2*pi;//角度归一化
            if (d > pi) d -= 2*pi;
            if (c < d) q[++tot] = {c, 1}, q[++tot] = {d, -1};//添加区间事件
            else q[++tot] = {-pi, 1}, q[++tot] = {d, -1},
            q[++tot] = {c, 1}, q[++tot] = {pi, -1};//跨越边界的情况
        }
    }
    for (i = n+1; i <= n+m; i++) {//遍历第二类点
        if (dis(p[i], p[x]) > R + R - eps) continue;
        ld a = get(p[x], p[i], R), b = atan2(p[i].y-p[x].y, p[i].x-p[x].x), c = b-a, d = b+a;
        if (c < -pi) c += 2*pi;
        if (d > pi) d -= 2*pi;
        if (c < d) q[++tot] = {c, -inf}, q[++tot] = {d, inf};
        else q[++tot] = {-pi, -inf}, q[++tot] = {d, inf},
        q[++tot] = {c, -inf}, q[++tot] = {pi, inf};
    }
    sort(q + 1, q + tot + 1);
    int t = 0;
    for (i = 1; i <= tot; i++) {
        if (t > 0 && i != 1 && q[i].x > q[i-1].x+eps) return true;//存在正权区间
        t += q[i].k;//更新计数
    }
    return false;
}


template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = x*10+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int main() {
    rd(n, m);
    if (m == 1) { puts("-1"); return 0; }//第二类点只有一个时
    int i;
    for (i = 1; i <= n; i++) rd(p[i].x, p[i].y);//第一类点的坐标
    random_shuffle(p+1, p+1+n);//随机打乱第一类点顺序
    for (i = 1; i <= m; i++) rd(p[i+n].x, p[i+n].y);//第二类点的坐标
    random_shuffle(p+n+1, p+1+m);//随机打乱第二类点顺序
    ld l = 0, r, mid;
    for (i = 1; i <= n+m; i++) if (check(i, l)) {//对每个点进行初始检查
        r = 1e9;//设置右边界
        while (r-l > 1e-5) {
            mid = (l+r)/2;
            if (check(i, mid)) l = mid; else r = mid;//更新边界
        }
    }
    if (l > 1e9-1) puts("-1");//解太大
    else printf("%.18Lf", l);
    return 0;
}