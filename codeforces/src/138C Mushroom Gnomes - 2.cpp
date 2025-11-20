//
// Created by Psy.C on 2025/11/20.
//
/*
*n: 第一类事件数量
m: 第二类事件数量
a[N]: 位置数组
h[N]: 高度/范围数组
l[N], r[N]: 左右概率参数
b[N]: 排序后的位置数组
p2[N]: 整数概率计数器
p[N]: 浮点概率数组
ans: 最终答案
c[N]: 位置-权重对数组
 *
*右边界影响：

找到位置a[i]右侧第一个位置的索引t
如果r[i]≠100，则在该位置乘以概率(M-r[i])/M
否则增加p2计数器
右范围边界：

找到位置a[i]+h[i]右侧第一个位置的索引t
如果r[i]≠100，则除以概率(M-r[i])/M来抵消影响
否则减少p2计数器
左边界影响：

找到位置a[i]左侧第一个位置的索引t
如果l[i]≠100，则除以概率(M-l[i])/M
否则减少p2计数器
左范围边界：

找到位置a[i]-h[i]左侧第一个位置的索引t
如果l[i]≠100，则乘以概率(M-l[i])/M来抵消影响
否则增加p2计数器
 *
*计算累积概率：当前概率乘以前一个累积概率
计算累积p2计数器
如果p2[i]为0(表示没有完全确定的事件)，则将权重乘以概率加入最终答案
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef long long ll;
typedef long double ld;
const ll N = 101000, M = 100;
ll n, m, a[N], h[N], l[N], r[N], b[N], p2[N];
ld p[N], ans;
pair<ll,ll> c[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    rep(i,N) p[i] = 1;
    rep(i,n) cin >> a[i] >> h[i] >> l[i] >> r[i];
    rep(i,m) cin >> c[i].first >> c[i].second;
    sort(c,c+m);
    rep(i,m) b[i] = c[i].first;
    rep(i,n) {
        ll t;
        t = upper_bound(b,b+m,a[i])-b;
        if (r[i] != M) p[t] *= (ld)(M - r[i]) / M;
        else p2[t]++;
        t = upper_bound(b,b+m,a[i]+h[i])-b;
        if (r[i] != M) p[t] /= (ld)(M - r[i]) / M;
        else p2[t]--;

        t = lower_bound(b,b+m,a[i])-b;
        if (l[i] != M) p[t] /= (ld)(M - l[i]) / M;
        else p2[t]--;
        t = lower_bound(b,b+m,a[i]-h[i])-b;
        if (l[i] != M) p[t] *= (ld)(M - l[i]) / M;
        else p2[t]++;
    }
    rep(i,m) {
        if (i) p[i] *= p[i-1];
        if (i) p2[i] += p2[i-1];
        if (!p2[i]) ans += (ld)c[i].second * p[i];
    }
    cout << fixed << setprecision(15) << ans;
    return 0;
}