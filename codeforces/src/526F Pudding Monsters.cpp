//
// Created by Psy.C on 2026/3/2.
//
/**
线段树数组，每个节点存储两个值
num[p][0]：区间最小值
num[p][1]：最小值的个数
mp[N]：映射数组，存储位置对应的值
mx[N], mn[N]：单调栈数组
t1, t2：单调栈的指针

维护最大值单调栈：

while (t1 > 0 && mp[mx[t1]] < mp[i])：维护单调递减栈
update(mx[t1-1]+1, mx[t1], 1, n, 1, -mp[mx[t1]])：更新区间 撤销之前最大值的贡献
t1--：弹出栈顶
维护最小值单调栈：

while (t2 > 0 && mp[mn[t2]] > mp[i])：维护单调递增栈
update(mn[t2-1]+1, mn[t2], 1, n, 1, mp[mn[t2]])：更新区间
t2--：弹出栈顶
统一更新：

update(1, i, 1, n, 1, -1)：区间[1,i]减1
mx[++t1] = mn[++t2] = i：当前元素入栈
区间调整：

update(mx[t1-1]+1, mx[t1], 1, n, 1, mp[i])：最大值影响区间
update(mn[t2-1]+1, mn[t2], 1, n, 1, -mp[i])：最小值影响区间
累加答案：ans += num[1][1]，累加当前最小值的个数


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+1;
int num[N<<2][2];
#define mid ((l+r)>>1)
void build(const int l, const int r, const int p) {
    num[p][1] = r - l + 1;
    if (l == r) return;
    build(l, mid, p<<1), build(mid+1, r, p<<1|1);
}

int tag[N<<2];
void modify(const int p, const int x) {//给节点p增加x值
    num[p][0] += x; tag[p] += x;
}

void update(const int L, const int R, const int l, const int r, const int p, const int val) {
    if (L <= l && r <= R) return modify(p, val);
    if (tag[p])
        modify(p<<1, tag[p]), modify(p<<1|1, tag[p]), tag[p] = 0;
    if (L <= mid) update(L, R, l, mid, p<<1, val);
    if (mid < R) update(L, R, mid+1, r, p<<1|1, val);
    num[p][0] = min(num[p<<1][0], num[p<<1|1][0]);
    num[p][1] = (num[p<<1][0] == num[p][0] ? num[p<<1][1] : 0) +
        (num[p<<1|1][0] == num[p][0] ? num[p<<1|1][1] : 0);
}

int n, mp[N], mx[N], mn[N], t1, t2;
ll ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y; mp[x] = y;
    }
    build(1, n, 1);
    for (int i = 1; i <= n; ++i) {
        while (t1 > 0 && mp[mx[t1]] < mp[i])
            update(mx[t1-1]+1, mx[t1], 1, n, 1, -mp[mx[t1]]), t1--;
        while (t2 > 0 && mp[mn[t2]] > mp[i])
            update(mn[t2-1]+1, mn[t2], 1, n, 1, mp[mn[t2]]), t2--;
        update(1, i, 1, n, 1, -1), mx[++t1] = mn[++t2] = i;
        update(mx[t1-1]+1, mx[t1], 1, n, 1, mp[i]);
        update(mn[t2-1]+1, mn[t2], 1, n, 1, -mp[i]);
        ans += num[1][1];
    }
    cout << ans << '\n';
    return 0;
}