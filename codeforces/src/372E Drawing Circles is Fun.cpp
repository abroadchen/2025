//
// Created by Psy.C on 2026/1/22.
//
/*
* 每次调用 calc() 都是因为发现了"下一组"
最后一组后面没有"下一组"，所以没有触发条件
因此必须在循环后手动处理最后一组
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define db double
#define N 1000
#define eps 1e-9
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define mod 1000000007ll
using namespace std;

//如果x<-eps返回-1，如果x>eps返回1，否则返回0
int sgn(const db x) { return x < -eps ? -1 : x > eps; }

struct node {
    db x, y;//坐标分量
    node() = default;
    node(const db x, const db y): x(x), y(y) {}
    friend node operator+(const node &a, const node &b) {
        return {a.x + b.x, a.y + b.y};
    }
    friend node operator-(const node a, const node b) {
        return {a.x - b.x, a.y - b.y};
    }
    friend node operator*(const node a, const db k) {
        return {a.x * k, a.y * k};
    }
    friend node operator/(const node a, const db k) {
        return {a.x / k, a.y / k};
    }
    friend db dot(const node a, const node b) {
        return a.x * b.x + a.y * b.y;
    }
    friend db cross(const node a, const node b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool eq(const node a, const node b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
    }
} p[N+5];

struct line {
    node m{}, v{};//m: 直线的中点 v: 直线的方向向量
    line() = default;
    line(const node m, const node v) : m(m), v(v) {}
} l[N*N+5];

//标准化方向向量: 确保方向向量指向特定方向（x为正或x为0时y为负)
node get(node a) {
    if (int k; (k = sgn(a.x)) < 0) a.x = -a.x, a.y = -a.y;
    else if (k == 0) {
        if (sgn(a.y) > 0) a.y = -a.y;
    }
    return a;
}

namespace mc {
    void inc(ll& x, const ll y) { x += y; if (x >= mod) x -= mod; }
    void dec(ll& x, const ll y) { x -= y; if (x < 0) x += mod; }
    ll add(ll x, const ll y) { inc(x, y); return x; }
    ll sub(ll x, const ll y) { dec(x, y); return x; }
}

ll tot, a[N*N+5], ans;
//tot: 当前处理的直线数量
//a: 存储相同直线的数量
void calc() {
    ll cur = 1;
    rep(i,tot) cur = cur * (a[i] + 1) % mod;//cur = ∏(ai+1) - 1 - ∑ai
    mc::dec(cur, 1);
    rep(i,tot) mc::dec(cur, a[i]);
    mc::inc(ans, cur);
    tot = 0;
}

int main() {
    fast;
    ll n; cin >> n;
    rep(i,n) {
        int a1, b, c, d; cin >> a1 >> b >> c >> d;
        const db x = static_cast<db>(a1)/b, y = static_cast<db>(c)/d,
        k = 1 / (x * x + y * y);
        p[i] = node(x, y) * k;//对点进行缩放
    }
    int cnt = 0;
    rep(i,n-1) for (int j = i + 1; j <= n; ++j) {//枚举所有点对
        cnt++;
        l[cnt].m = (p[i] + p[j]) / 2;
        l[cnt].v = get(p[i] - p[j]);
    }
    sort(l + 1, l + cnt + 1, [](const line &a, const line &b) {
        int k;//按中点坐标排序（先x后y)
        if ((k = sgn(a.m.x - b.m.x)) != 0) return k < 0;
        if ((k = sgn(a.m.y - b.m.y)) != 0) return k < 0;
        return sgn(cross(a.v, b.v)) == 1;//相同中点时按方向向量排序
    });
    rep(i,cnt) {
        if (i == 1 || !eq(l[i].m, l[i-1].m)) {//如果中点不同：计算前一组，开始新组
            if (i != 1) calc();
            a[++tot] = 1;
        } else if (sgn(cross(l[i].v, l[i-1].v)) == 0) a[tot]++;//如果方向相同（叉积为0）：加入当前组
        else a[++tot] = 1;//如果方向不同：开始新组
    }
    calc();//计算最后一组
    cout << ans << '\n';
    return 0;
}