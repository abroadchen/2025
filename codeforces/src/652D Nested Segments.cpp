//
// Created by Psy.C on 2026/4/4.
//
///时间复杂度：O(n log n)，空间复杂度：O(n)
///unique() 函数返回指向唯一元素范围末尾的迭代器，减去 b（起始地址）后得到长度，再减去 1 得到索引计数。
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
struct node {
    int l, r, id;
    bool operator<(const node &o) const {
        if (l == o.l) return r > o.r;
        return l < o.l;
    }
} L[N];
///获取x的最低位1及其后面的0构成的数值
int low_bit(int x) { return x & -x; }
int n, c[N];
void update(int x, int y) {
    for (int i = x; i <= n; i += low_bit(i)) c[i] += y;
}
int query(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= low_bit(i)) ans += c[i];
    return ans;
}

int b[N], ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> L[i].l >> L[i].r; L[i].id = i;//n个区间
        b[i] = L[i].r;//离散化数组 将右端点保存到b数组中
    }
    sort(L + 1, L + n + 1);
    sort(b + 1, b + n + 1);
    int pos = unique(b + 1, b + n + 1) - b - 1;//离散化后的元素个数
    for (int i = 1; i <= n; ++i)
        L[i].r = lower_bound(b + 1, b + pos + 1, L[i].r) - b;//用二分查找重新映射右端点值
    for (int i = n; i >= 1; --i) {
        update(L[i].r, 1);//更新当前区间的右端点在树状数组中的计数
        ans[L[i].id] = query(L[i].r - 1);//查询比当前右端点小的位置的区间数量（即被当前区间完全包含的区间数）
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
    return 0;
}