//
// Created by Psy.C on 2026/3/5.
//
/**
 * 将(x,y)转换为(t+x+y)/2和(t+x-y)/2，将二维问题转化为一维问题
 *
T: 时间周期参数
node结构体包含：p(商), x(位置), w(余数)
构造函数将时间t分解为 t/T 和 t%T
重载 < 操作符，先按w排序，再按p排序
mxx: 若x<y则更新x=y
mnn: 若x>y则更新x=y
fd: 向下取整除法（floor division）
cd: 向上取整除法（ceiling division）

检查序列是否可行
inf, sup: 增量的上下界
添加哨兵节点 g[n]
遍历相邻节点，计算约束条件
确定增量incr
根据约束构造序列
使用fill和iota填充数组
adjacent_difference计算相邻差分 得到0/1序列

a1, a2: 存储两个维度的结果
a: 字符数组 {'L','U','D','R'}，ASCII码为{76,85,68,82}
读入n和T，n自增1
读入每个时刻的坐标约束
检查奇偶性约束：(t^x^y)&1 检查是否满足行走约束
构造两个序列：g1和g2
如果任一序列不可行，输出"NO"
否则根据a1和a2的组合输出路径字符
a1[i]|a2[i]<<1 将两个布尔值组合成索引，选择对应字符

dT: 时间段内完整周期数的变化
dt: 时间段内余数部分的变化
ds: 要求的总变化量
情况1：dT == 0（同一周期内）
如果在同一周期内，变化量必须在[0, dt]范围内
情况2：dT > 0（跨越周期，递增）
cd(ds-dt, dT): 增量的下界，确保变化不会太大
fd(ds, dT): 增量的上界，确保变化不会太小
情况3：dT < 0（跨周期，递减）
处理反向情况，逻辑类似

如果约束矛盾则失败
选择中点作为增量值
确保差值在合理范围内
使用fill填充不变部分
使用iota填充递增部分

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+50, M = 2e6+50;

int T;
struct node {
    ll p, x; int w;
    node(const ll t=0, const ll pos=0) : p(t/T), x(pos), w(t%T) {}
    bool operator<(const node& o) const {
        return w < o.w || (w == o.w && p < o.p);
    }
} g1[N], g2[N];

inline void mxx(ll& x, const ll y) { x < y ? x = y : 0; }
inline void mnn(ll& x, const ll y) { x > y ? x = y : 0; }
inline ll fd(const ll x, const ll y) {
    auto [quot, rem] = lldiv(x, y);
    return quot + (rem >> 63);
}
inline ll cd(const ll x, const ll y) {
    auto [quot, rem] = lldiv(x, y);
    return quot + (rem > 0);
}

int n;
ll buf[M];
bool ok(node *g, int *ans) {
    int i, la=0, cur;
    ll inf=0, sup=T, incr;
    g[n].p = -1, g[n].w = T, g[n].x = 0;//确保覆盖整个区间[0,T]
    sort(g, g + (n+1));
    for (i = 1; i <= n && inf <= sup; ++i) {
        ll dT = g[i].p - g[i - 1].p, dt = g[i].w - g[i - 1].w, ds = g[i].x - g[i - 1].x;
        if (!dT) {
            if (ds < 0 || ds > dt) return false;
        } else if (dT > 0) {
            if (ds < 0) return false;
            mxx(inf, cd(ds-dt, dT)), mnn(sup, fd(ds, dT));
        } else {
            if (ds > 0) return false;
            mxx(inf, cd(-ds, -dT)), mnn(sup, fd(-ds+dt, -dT));
        }
    }
    if (inf > sup) return false;
    incr = (inf + sup) >> 1, *buf = 0;
    for (i = 0; i <= n; ++i, la = cur) {
        cur = g[i].w;
        buf[cur] = g[i].x - incr*g[i].p;//计算该位置的值
        assert(0 <= buf[cur] - buf[la] && buf[cur] - buf[la] <= cur - la);
        const auto mid = buf + cur - int(buf[cur] - buf[la]);
        fill(buf + la, mid, buf[la]);
        iota(mid, buf + cur, buf[la]);
    }
    return adjacent_difference(buf + 1, buf + (T + 1), ans), true;
}

int a1[M], a2[M];
char a[] = {76, 85, 68, 82};
int main() {
    fast;
    cin >> n >> T; ++n;
    ll t, x, y;
    for (int i = 1; i < n; ++i) {
        cin >> t >> x >> y;
        if ((t^x^y)&1) return cout << "NO\n", 0;
        g1[i] = {t, (t+x+y)/2};
        g2[i] = {t, (t+x-y)/2};
    }
    if (!(ok(g1, a1) && ok(g2, a2))) return puts("NO"), 0;
    for (int i = 0; i < T; ++i) putchar(a[a1[i]|a2[i]<<1]);
    return putchar(10), 0;
}