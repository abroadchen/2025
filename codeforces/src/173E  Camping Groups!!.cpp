//
// Created by Psy.C on 2025/11/29.
//
/*
*N: 最大数量级
n: 人员总数
k: 能力值差阈值
ta, tr: 离散化后的坐标数量
Q: 查询数量
val[N]: 每个人能匹配的人数
hs[N]: 人员按r值排序后的排名
ans[N]: 查询结果
per: 人员结构体(r: 声望值, a: 能力值, id: 编号)
qu: 查询结构体(x,y: 两人编号, id: 查询编号)
sa,sr: 存储所有能力值和声望值的集合(用于离散化)
mpa,mpr: 能力值和声望值的映射(离散化映射)
 *
*实现树状数组用于高效区间求和：
add(x,v): 在位置x增加v
qsum(x): 查询[1,x]区间和
 *
*实现线段树用于区间最值查询：
modify: 单点更新最大值
qmx: 区间查询最大值
 *
*读入人员的声望值和能力值
使用set进行离散化，建立映射关系
在能力值集合中额外插入a±k是为了后续查询边界处理
 *
*使用滑动窗口和树状数组计算：
按能力值排序人员
对每个人i，维护能力值差≤k的人员窗口
用树状数组统计声望值≤当前人的人员数量
 *
*按声望值降序重新排列人员
hs数组记录每个人在新排序中的位置
按查询涉及两人的最大声望值降序排列查询
 *
*维护声望值≥查询涉及两人最大声望值的人员集合
对这些人员在线段树中按能力值维护其可匹配人数的最大值
对查询的两人，确定能力值有效区间[y-k, x+k]
在此区间内查询最大可匹配人数
 *
 *
*时间复杂度：O((n+Q)log n)
空间复杂度：O(n)
 *
 */
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 3e5+5;
int n, k, ta, tr, Q,
val[N], hs[N], ans[N];

struct per { int r, a, id; } p[N];
struct qu { int x, y, id; } q[N];
set<int> sa,sr;
map<int,int> mpa,mpr;

int sum[N];
void add(const int x, const int v) {//函数内部不能被修改 只读
    for (int i = x; i <= tr; i += i & -i) sum[i] += v;
}
int qsum(const int x) {
    int res = 0;
    for (int i = x; i; i -= i & -i) res += sum[i];
    return res;
}

#define ls x<<1
#define rs (x<<1|1)
int mx[N<<2];
void modify(const int x, const int l, const int r, const int u, const int v) {
    if (l ^ r) {
        const int mid = (l + r) >> 1;
        if (u <= mid) modify(ls, l, mid, u, v);
        else modify(rs, mid + 1, r, u, v);
        mx[x] = max(mx[ls], mx[rs]);
    } else mx[x] = max(mx[x], v);
}

int qmx(const int x, const int l, const int r, const int ql, const int qr) {
    if (ql <= l && r <= qr) return mx[x];
    const int mid = (l + r) >> 1; int ret = -1;
    if (ql <= mid) ret = max(ret, qmx(ls, l, mid, ql, qr));
    if (qr > mid) ret = max(ret, qmx(rs, mid + 1, r, ql, qr));
    return ret;
}

int main() {
    fast;
    cin>>n>>k;
    for (auto& i : mx) i = -1;
    rep(i,n) {
        cin >> p[i].r; sr.insert(p[i].r);
        p[i].id = i;
    }
    for (int i : sr) mpr[i] = ++tr;
    rep(i,n) {
        cin >> p[i].a; sa.insert(p[i].a);
        sa.insert(p[i].a - k);
        sa.insert(p[i].a + k);
    }
    for (int i : sa) mpa[i] = ++ta;
    cin>>Q;
    rep(i,Q) { cin>>q[i].x>>q[i].y; q[i].id = i; }
    sort(p + 1, p + 1 + n, [](const per i, const per j) {
        return i.a < j.a;
    });
    for (int i = 1, l = 0, r = 0; i <= n; ++i) {
        for (; r < n && p[r + 1].a - p[i].a <= k; ++r) {
            add(mpr[p[r+1].r], 1);
        }
        for (; l < r && p[i].a - p[l+1].a > k; ++l) {
            add(mpr[p[l+1].r], -1);
        }
        val[p[i].id] = qsum(mpr[p[i].r]);
    }
    sort(p + 1, p + 1 + n, [](const per i, const per j) {
        return i.r > j.r;
    });
    rep(i,n) hs[p[i].id] = i;
    sort(q + 1, q + 1 + Q, [](const qu i, const qu j) {
        return max(p[hs[i.x]].r, p[hs[i.y]].r) >
            max(p[hs[j.x]].r, p[hs[j.y]].r);
    });
    for (int i = 1, j = 0, x, y; i <= Q; ++i) {
        for (; j < n && p[j+1].r >= max(p[hs[q[i].x]].r, p[hs[q[i].y]].r); ++j) {
            modify(1, 1, ta, mpa[p[j+1].a], val[p[j+1].id]);
        }
        x = min(p[hs[q[i].x]].a, p[hs[q[i].y]].a);
        y = max(p[hs[q[i].x]].a, p[hs[q[i].y]].a);
        if (y - k > x + k) { ans[q[i].id] = -1; continue; }
        ans[q[i].id] = qmx(1, 1, ta, mpa[y-k], mpa[x+k]);
    }
    rep(i,Q) cout << ans[i] << '\n';
    return 0;
}