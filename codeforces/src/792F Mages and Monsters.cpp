//
// Created by Psy.C on 2026/9/15.
//
/**
key 为 x 坐标，value 为 y 坐标，保证 mp 里的点构成一条凸包折线（x 严格递增）
cmp 决定凸包是上凸（geq，取"在某 x 处最高点"）‍还是下凸。main 里传入 geq（a >= b），所以是求最大值的上凸包
lower_bound(x) 找第一个 x ≥ 给定 x 的点。
若某点 x 已存在：若 cmp(y, 已有y)（即 y 不如已有的好），说明这个点不值得插 → 返回 true。
否则检查叉积 area(prev, cur, new) 的符号。对上凸包（geq）‍，若叉积 ≥ 0 说明新点在凸包内部/下方，无需插入。
一句话：check = "这点的加入能否改变凸包？"不能就返回 true（表示"已被覆盖，不用插"）
对中间点 i，检查它的前驱 j 和后继 k。若 area(j,k,i) 表明 i 使折线"拐错了方向"（不满足凸性），则删掉 i
插入后，不断 remove 前驱、后继，直到两侧都满足凸性。这就是动态插入点的凸包维护（类似增量法）

找包含 x 的那段折线区间 [j, i]，用线性插值算出 x 处的高度。
若 x 超出凸包右边界（i == mp.end()）返回 -1。
这本质是在支持"给定斜率/横坐标，求凸包上对应最大值"。因为凸包是上凸的，它在任意 x 的最大值就是凸包折线在该 x 的高度
强制在线：x,y,t,h 都用 (原始 + j) % mod + 1 加密，j 是上一次成功查询时的下标——只有在线计算才能解出真实值，无法离线预处理。
op == 1：往凸包里插入一个点 (x,y)。
op == 2：查询点 (t,h) 是否满足条件。
关键解释查询逻辑：

计算 1.0*h/t（斜率），用 v.query(斜率) 在凸包上找：是否存在一条"截距 = 该斜率对应位置"的点，使高度满足要求。
检查 cps * t <= m + eps：这相当于判断直线 y = (斜率)*t 与凸包的关系，即"在点 (t,h) 处，凸包高度截距 cps 乘 t 是否不超过容量 m"。
满足则 j = i 并输出 YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
#define db double
#define eps 1e-7
using namespace std;
constexpr int mod = 1e6;
namespace {
    struct Point {
        int x, y;
        Point() = default;
        Point(int a, int b) : x(a), y(b) {}
        Point(ii p) : x(p.first), y(p.second) {}
        bool operator<(const Point& o) const {
            return x == o.x ? y < o.y : x < o.x;
        }
        ll operator*(const Point& o) const {
            return 1ll*x*o.y - 1ll*y*o.x;
        }
        Point operator-(const Point& o) const {
            return {x - o.x, y - o.y};
        }
    };
}

namespace {
    ll area(Point a, Point b, Point c) { return (b-a)*(c-a); }
}

namespace {
    struct DynamicConvexHull {
        function<bool(ll, ll)> cmp;
        map<int, int> mp;
        DynamicConvexHull(function<bool(ll, ll)> cmp) : cmp(std::move(cmp)) {}

        bool check(int x, int y) {
            auto i = mp.lower_bound(x);
            if (i == mp.end()) return false;
            if (i->first == x) return cmp(y, i->second);
            if (i == mp.begin()) return false;
            return cmp(area(Point(*prev(i)), Point(*i), Point(x, y)), 0);
        }
        bool remove(auto i) {
            if (i == mp.begin()) return false;
            auto j = prev(i), k = next(i);
            if (k == mp.end()) return false;
            if (cmp(area(Point(*j), Point(*k), Point(*i)), 0))
                return mp.erase(i), true;
            return false;
        }
        void insert(int x, int y) {
            if (check(x, y)) return;//已被覆盖，跳过
            mp[x] = y;//插入
            auto i = mp.find(x);
            if (i != mp.begin()) while (remove(prev(i))) {}//向左清理
            if (next(i) != mp.end()) while (remove(next(i))) {}//向右清理
        }
        db query(db x) {
            auto i = mp.lower_bound((ll)ceil(x));
            if (i == mp.end()) return -1;
            if (i->first == x) return i->second;
            auto j = prev(i);
            return j->second + (i->second - j->second)*(x - j->first)/(i->first - j->first);
        }
    };
}


int main() {
    fast;
    function<bool(ll, ll)> geq = [&](ll a, ll b) { return a >= b; };
    DynamicConvexHull v(geq); v.insert(0, 0);
    int q; ll m; cin >> q >> m;
    for (int i = 1, j = 0, op, a, b; i <= q; ++i) {
        cin >> op >> a >> b;
        if (op == 1) {
            int x = (a + j) % mod + 1, y = (b + j) % mod + 1;
            v.insert(x, y);
        } else {
            int t = (a + j) % mod + 1, h = (b + j) % mod + 1;
            db cps = v.query(1.0*h/t);
            if (cps != -1 && cps*t <= m + eps) j = i, cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}