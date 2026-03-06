//
// Created by Psy.C on 2026/3/6.
//
/**
n, m: 两种区间数量
l[N], r[N]: 第一类区间[left, right]
lsh[N]: 离散化数组
tot: 离散化后元素数量
a[N], b[N], c[N]: 第二类区间及其权重
u[N], q[N]: 按右端点分组的容器
ans: 答案
res: 最优解的索引对
pre[N], suf[N]: 前缀和后缀信息

对所有端点排序并去重
将原始坐标映射到离散化后的索引
u[r[i]]: 存储右端点为r[i]的第一类区间
q[b[i]]: 存储右端点为b[i]的第二类区间
对于每个右端点i，将对应的第一类区间更新到线段树
查询第二类区间在[a[id], b[id]]范围内的最优第一类区间
计算并更新最大收益

pre[i]: 在位置i左侧（包含）的区间中最远的右端点
suf[i]: 在位置i右侧（包含）的区间中最近的左端点
前缀最大值和后缀最小值预处理
检查每个第二类区间是否能与前面或后面的区间产生交集
计算交集长度与权重的乘积作为收益

时间复杂度：O((n+m)log(n+m))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
#define mid ((l+r)>>1)
using namespace std;
constexpr int N = 8e5+1;

ii mx[N<<2];
void update(int k, int l, int r, int pos, ii v) {
    mx[k] = max(mx[k], v);
    if (l == r) return;
    if (pos <= mid) update(k<<1, l, mid, pos, v);
    else update(k<<1|1, mid+1, r, pos, v);
}

ii query(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R) return mx[k];
    if (R <= mid) return query(k<<1, l, mid, L, R);
    if (L > mid) return query(k<<1|1, mid+1, r, L, R);
    return max(query(k<<1, l, mid, L, R), query(k<<1|1, mid+1, r, L, R));
}

int n, m, l[N], r[N], lsh[N], tot, a[N], b[N], c[N], ans;
vector<int> u[N], q[N];
ii res, pre[N], suf[N];
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> l[i] >> r[i], lsh[++tot] = l[i], lsh[++tot] = r[i];
    for (int i = 1; i <= m; ++i)
        cin >> a[i] >> b[i] >> c[i], lsh[++tot] = a[i], lsh[++tot] = b[i];
    sort(lsh + 1, lsh + tot + 1);
    tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1;
    for (int i = 1; i <= n; ++i)
        l[i] = lower_bound(lsh + 1, lsh + tot + 1, l[i]) - lsh,
            r[i] = lower_bound(lsh + 1, lsh + tot + 1, r[i]) - lsh;
    for (int i = 1; i <= m; ++i)
        a[i] = lower_bound(lsh + 1, lsh + tot + 1, a[i]) - lsh,
            b[i] = lower_bound(lsh + 1, lsh + tot + 1, b[i]) - lsh;
    for (int i = 1; i <= n; ++i) u[r[i]].push_back(i);
    for (int i = 1; i <= m; ++i) q[b[i]].push_back(i);
    for (int i = 1; i <= tot; ++i) {
        for (auto id : u[i]) update(1, 1, tot, l[id], {lsh[r[id]]-lsh[l[id]], id});
        for (auto id : q[i]) {
            auto t = query(1, 1, tot, a[id], b[id]);
            if (t.first*c[id] > ans) ans = t.first*c[id], res = {t.second, id};
        }
    }
    memset(suf, 0x3f, sizeof(suf));
    for (int i = 1; i <= n; ++i)
        pre[l[i]] = max(pre[l[i]], {r[i], i}),
            suf[r[i]] = min(suf[r[i]], {l[i], i});
    for (int i = 1; i <= tot; ++i) pre[i] = max(pre[i], pre[i-1]);
    for (int i = tot; i >= 1; --i) suf[i] = min(suf[i], suf[i+1]);
    for (int i = 1; i <= m; ++i) {
        if (pre[a[i]].first >= 1 && pre[a[i]].first <= tot)
            if (min(lsh[b[i]]-lsh[a[i]], lsh[pre[a[i]].first]-lsh[a[i]])*c[i] > ans)
                ans = min(lsh[b[i]]-lsh[a[i]], lsh[pre[a[i]].first]-lsh[a[i]])*c[i],
                    res = {pre[a[i]].second, i};
        if (suf[b[i]].first >= 1 && suf[b[i]].first <= tot)
            if (min(lsh[b[i]]-lsh[a[i]], lsh[b[i]]-lsh[suf[b[i]].first])*c[i] > ans)
                ans = min(lsh[b[i]]-lsh[a[i]], lsh[b[i]]-lsh[suf[b[i]].first])*c[i],
                    res = {suf[b[i]].second, i};
    }
    cout << ans << '\n';
    if (ans) cout << res.first << ' ' << res.second;
    return 0;
}