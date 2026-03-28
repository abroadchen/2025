//
// Created by Psy.C on 2026/3/28.
//
/**
p[i]: 第i项的概率权重
num[i]: 第i项的当前计数值（被选中的次数）
a[i]: 第i项的初始参数
l, r: 区间范围
mni, mxi: 最小值和最大值的位置索引
ans: 区间内的期望值
mn, mx: 区间的最小增量和最大增量

ans: 当前元素的贡献值
mx: 添加一个单位后的边际收益
mn: 移除一个单位后的边际损失
计算位置i对总期望值的贡献
p[i]*num[i]/(num[i]+a[i])：基于当前状态的概率加权值
p[i]/2.：理论最大值的一半
取两者的最小值，保证合理范围
在位置i增加一个单位后能带来的边际收益
条件判断：如果当前num[i] >= a[i]，说明已达到平衡，不能再获得正收益，所以mx = 0
计算公式：新状态的贡献值减去旧状态的贡献值
新状态：p[i]*(num[i]+1)/(num[i]+a[i]+1)
旧状态：p[i]*num[i]/(num[i]+a[i])
差值就是增加一个单位的收益
在位置i减少一个单位会造成的损失（正值表示损失）
三种情况：
num[i] == 0：没有单位可减，设置为无穷大inf
num[i] > a[i]：过多单位，减少不会造成损失，mn = 0
其他情况：旧状态的贡献值减去新状态的贡献值
旧状态：p[i]*num[i]/(num[i]+a[i])
新状态：p[i]*(num[i]-1)/(num[i]+a[i]-1)
差值表示减少一个单位的损失
记录当前节点最大值和最小值的位置都是i
因为这是一个叶子节点，所以最大值和最小值都在同一个位置
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define di pair<double, int>
using namespace std;
constexpr int N = 2e5+5;
constexpr double inf = 1e18;
double p[N];
int num[N], a[N];
struct sgt {
    struct node { int l, r, mni, mxi; double ans, mn, mx; } tr[N<<2];
#define ls k<<1
#define rs (k<<1|1)
    ///合并左右子节点信息，更新当前节点的值
    void push_up(int k) {
        tr[k].ans = tr[ls].ans + tr[rs].ans;
        if (tr[ls].mx > tr[rs].mx)
            tr[k].mx = tr[ls].mx, tr[k].mxi = tr[ls].mxi;
        else tr[k].mx = tr[rs].mx, tr[k].mxi = tr[rs].mxi;
        if (tr[ls].mn < tr[rs].mn)
            tr[k].mn = tr[ls].mn, tr[k].mni = tr[ls].mni;
        else tr[k].mn = tr[rs].mn, tr[k].mni = tr[rs].mni;
    }
    void get(int k, int i) {
        tr[k].ans = min(p[i]*num[i]/(1.*(num[i]+a[i])),p[i]/2.);
        if (num[i] >= a[i]) tr[k].mx = 0;
        else tr[k].mx = p[i]*(num[i]+1)/(1.*(num[i]+a[i]+1))-
            p[i]*num[i]/(1.*(num[i]+a[i]));
        if (num[i] == 0) tr[k].mn = inf;
        else if (num[i] > a[i]) tr[k].mn = 0;
        else tr[k].mn = p[i]*num[i]/(1.*(num[i]+a[i]))-
            p[i]*(num[i]-1)/(1.*(num[i]+a[i]-1));
        tr[k].mxi = tr[k].mni = i;
    }
    void build(int k, int l, int r) {
        tr[k].l = l, tr[k].r = r;
        if (l == r) { get(k, l); return; }
        int mid = (l+r)>>1;
        build(ls, l, mid); build(rs, mid+1, r);
        push_up(k);
    }
    void modify(int k, int x) {
        if (tr[k].l == tr[k].r) { get(k, x); return; }
        int mid = (tr[k].l + tr[k].r)>>1;
        if (x <= mid) modify(ls, x);
        else modify(rs, x);
        push_up(k);
    }
    double query() { return tr[1].ans; }
    di qmx() { return {tr[1].mx, tr[1].mxi}; }
    di qmn() { return {tr[1].mn, tr[1].mni}; }
} T;

int n, t, q;
int main() {
    fast;
    cin >> n >> t >> q;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    T.build(1, 1, n);
    for (int i = 1; i <= t; ++i) {
        int x = T.qmx().second;
        num[x] += 1;
        T.modify(1, x);
    }
    while (q--) {
        int op, i; cin >> op >> i;
        a[i] += op == 1 ? 1 : -1;
        T.modify(1, i);
        while (T.qmx().first > T.qmn().first) {
            int x = T.qmx().second, y = T.qmn().second;
            num[x] += 1; num[y] -= 1;
            T.modify(1, x); T.modify(1, y);
        }
        printf("%.8f\n", T.query());
    }
    return 0;
}