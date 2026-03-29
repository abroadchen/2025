//
// Created by Psy.C on 2026/3/28.
//
/**
x: 站点位置
p: 站点油价
d: 总路程
n: 油箱最大容量
m: 加油站数量
st[N]: 单调栈，存储索引
tp: 栈顶指针
t[N]: 每个位置右侧最近的更便宜站点索引
ans: 总费用
在终点添加一个虚拟站点，价格设为-1（表示不需要加油）

从后往前遍历
维护价格单调递减的栈
t[i] 存储站点i右侧最近的更便宜或等价站点索引

a[t[i]].x - a[i].x: 到下一个更便宜站点的距离
min(..., n): 不超过油箱容量
- now: 减去当前油量
max(0, ...) : 确保不为负数
在当前站点加油dis单位
费用为dis * price
减去行驶到下一位置消耗的油量
加上之前多加的油量dis

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

struct node {
    int x, p;
    bool operator<(const node &o) const {
        return x < o.x;
    }
} a[N];

int d, n, m, st[N], tp, t[N];
ll ans;
int main() {
    fast;
    cin >> d >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i].x >> a[i].p;
    sort(a + 1, a + m + 1);
    a[m+1].x = d, a[m+1].p = -1;
    st[++tp] = m + 1;
    for (int i = m; i; --i) {
        while (tp && a[st[tp]].p > a[i].p) tp--;
        t[i] = st[tp];
        st[++tp] = i;
    }
    int now = n;
    for (int i = 0; i <= m; ++i) {
        int dis = max(0, min(a[t[i]].x - a[i].x, n) - now);
        ans += 1ll*dis*a[i].p;
        now -= a[i+1].x - a[i].x - dis;
        if (now < 0) return puts("-1"), 0;
    }
    cout << ans << '\n';
    return 0;
}