//
// Created by Psy.C on 2026/4/23.
//
/**
重载+=操作符，实现pll类型的加法赋值
重载+操作符，实现pll类型的加法运算
cnt: 树状数组存储数据
add: 在位置x增加v（单点更新）
vis_cnt: 查询前x项的和（前缀和查询）
m: 数组大小
mn: 记录最小值的数组
bit: 存储pll类型的树状数组
add: 在位置x添加值v，并更新mn[i]为最小值p
查询前x项的pll和
查询区间内mn的最小值
f, g: 动态规划数组
p: 排序后的前缀和数组
sum: 前缀和数组
O: 零值对
infp: 负无穷大对
X: 未被覆盖的位置数组
xp: 前缀最小值数组

重置所有数组
初始化树状数组
遍历每个位置i
使用二分查找定位前缀和位置
更新树状数组
计算当前贡献T并累加到S
收集未被覆盖的位置到X数组
动态规划求解最大值
最终返回答案对

读入n和K
构建前缀和数组sum
将所有前缀和去重排序
设置二分搜索范围
计算前缀最小值数组xp
二分搜索最优的C值
根据check函数返回的第二维值调整搜索范围
用找到的最优C值重新计算
输出最终答案


lower_bound(p+1, p+m+1, sum[i-1]): 找到前缀和sum[i-1]在离散化数组中的位置
add(pos, {-sum[i-1], 1ll}, i-1): 在树状数组中记录贡献值{-sum[i-1], 1}和位置i-1
upper_bound(...) - 1: 找到满足条件的最大索引
query(pos): 查询累积的贡献
find(pos): 找到相关的最小位置
vis_cnt(i): 检查位置i是否被覆盖（通过树状数组查询）
X数组存储所有未被覆盖的位置
添加哨兵X[Q+1] = n+1简化后续处理
在每个连续的未覆盖区间内进行动态规划
mx = max(...)寻找当前区间内的最优决策
dp状态转移，考虑跨越多个区间的最优策略
-xp[X[1]-1]和-xp[X[i+1]-1]表示考虑前缀最小值的代价

加负号的目的是：将其作为初始代价或惩罚项
f[i] 是当前区间的最优收益
xp[X[i+1]-1] 是从开始到下一区间的前缀最小值
f[i]-xp[X[i+1]-1] 实际上是在计算净收益：当前收益减去未来可能的代价
sum[j]-C 是当前选择的收益减去单位成本
当我们加上 dp 时，如果 dp 包含负的前缀最小值项，这会正确地累计代价

 */
#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define low_bit(x) (x&-x)
using namespace std;
constexpr int N = 1e5+7;
constexpr ll inf = 1e18;

pll operator+=(pll &x, pll y) {
    x.first += y.first; x.second += y.second;
    return x;
}
pll operator+(pll a, pll b) {
    return {a.first + b.first, a.second + b.second};
}

int cnt[N], n;
void add(int x, int v) {
    for (int i = x; i <= n; i += low_bit(i))
        cnt[i] += v;
}
int vis_cnt(int x, int v=0) {
    for (int i = x; i; i -= low_bit(i))
        v += cnt[i];
    return v;
}

int m, mn[N];
pll bit[N];
void add(int x, pll v, int p) {
    for (int i = x; i <= m; i += low_bit(i))
        bit[i] += v, mn[i] = min(mn[i], p);
}
pll query(int x, pll res={0, 0}) {
    for (int i = x; i; i -= low_bit(i))
        res += bit[i];
    return res;
}
int find(int x, int res=n+1) {
    for (int i = x; i; i -= low_bit(i))
        res = min(res, mn[i]);
    return res;
}
#undef low_bit

ll f[N], g[N], p[N], sum[N];
pll O = {0, 0}, infp = {-inf, -inf};
int X[N], xp[N];
pll check(ll C) {
    for (int i = 1; i <= n+1; ++i)
        f[i] = g[i] = cnt[i] = 0, mn[i] = n+1, bit[i] = O;
    pll S = O;
    for (int i = 1; i <= n; ++i) {
        int pos = lower_bound(p+1, p+m+1, sum[i-1]) - p;
        add(pos, {-sum[i-1], 1ll}, i-1);
        pos = upper_bound(p+1, p+m+1, sum[i]-C) - p - 1;
        pll T = query(pos); T.first += T.second*(sum[i]-C);
        pos = find(pos), S += T;
        if (pos < n) add(pos+1, 1), add(i+1, -1);
    }
    int Q = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis_cnt(i)) X[++Q] = i;
    X[++Q] = n+1;
    pll dp = {0, 0}; dp = max(dp, {-xp[X[1]-1], 0});
    for (int i = 1; i < Q; ++i) {
        pll mx = infp;
        for (int j = X[i]; j < X[i+1]; ++j)
            mx = max(mx, make_pair(sum[j]-C, 1ll) + dp);
        f[i] = mx.first, g[i] = mx.second;
        dp = max(dp, {f[i]-xp[X[i+1]-1], g[i]});
    }
    return make_pair(f[Q-1], g[Q-1]) + S;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll K;
int main() {
    n = rd(); scanf("%lld", &K); p[m=1] = 0;
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i-1] + rd(), p[++m] = sum[i];
    sort(p + 1, p + m + 1);
    m = unique(p+1, p+m+1) - p - 1;
    ll l = -1e10, r = 1e10, ans = 0, mn = 0;
    for (int i = 1; i <= n; ++i)
        mn = min(mn, sum[i]), xp[i] = mn;
    while (l <= r) {
        ll mid = (l+r)>>1;
        pll pd = check(mid);
        if (pd.second < K) r = mid-1;
        else l = mid+1, ans = mid;
    }
    pll res = check(ans);
    ans = res.first + K*ans;
    printf("%lld\n", ans);
    return 0;
}