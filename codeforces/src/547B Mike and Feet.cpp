//
// Created by Psy.C on 2026/3/8.
//
/**
设置边界值a[0]和a[n+1]为负无穷
使用单调递减栈找到每个元素左边第一个更小的元素位置
l[i]：a[i]左边第一个小于a[i]的元素位置
从右往左遍历
找到每个元素右边第一个更小的元素位置
r[i]：a[i]右边第一个小于a[i]的元素位置
len[i]：以a[i]为最小值的连续子数组的最大长度
即：从l[i]+1到r[i]-1的长度

调用get()函数计算每个元素作为最小值的区间长度
对于每个元素，将以它为最小值的区间长度作为位置，更新线段树
查询并输出：对于长度为i到n的区间，能形成的最小值的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, inf = 2147483647;

int tr[N<<2];
void push_up(int o) { tr[o] = max(tr[o<<1], tr[o<<1|1]); }

void update(int o, int l, int r, int x, int val) {
    if (l == r) { tr[o] = max(tr[o], val); return; }
    int mid = (l + r) >> 1;
    if (x <= mid) update(o<<1, l, mid, x, val);
    if (x > mid) update(o<<1|1, mid+1, r, x, val);
    push_up(o);
}

int query(int o, int l, int r, int L, int R) {
    int res = 0;
    if (L <= l && R >= r) return tr[o];
    int mid = (l + r) >> 1;
    if (L <= mid) res = max(res, query(o<<1, l, mid, L, R));
    if (R > mid) res = max(res, query(o<<1|1, mid+1, r, L, R));
    return res;
}

int a[N], n, top, st[N], l[N], r[N], len[N];
void get() {
    a[0] = a[n+1] = -inf;
    top = 0; st[++top] = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[st[top]] >= a[i]) top--;
        l[i] = st[top];
        st[++top] = i;
    }
    top = 0; st[++top] = n+1;
    for (int i = n; i >= 1; --i) {
        while (top && a[st[top]] >= a[i]) top--;
        r[i] = st[top];
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i) len[i] = r[i] - l[i] - 1;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i]; get();
    for (int i = 1; i <= n; ++i) update(1, 1, n, len[i], a[i]);
    for (int i = 1; i <= n; ++i) cout << query(1, 1, n, i, n) << ' ';
    return 0;
}