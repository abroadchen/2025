//
// Created by Psy.C on 2026/4/18.
//
/**
mp: 记录每个值最后出现的位置
lst[N]: 记录每个位置上相同值的上一次出现位置
a[N]: 原数组
x[N]: 异或前缀和数组
m: 查询数量
ans[N]: 存储答案
x[i] = x[i-1]^a[i]: 计算异或前缀和
lst[i] = mp[a[i]]: 记录a[i]上一次出现的位置
mp[a[i]] = i: 更新a[i]的最新位置

树状数组更新：
if (lst[i]) add(lst[i], a[i]): 如果a[i]之前出现过，在上次出现位置异或a[i]
add(i, a[i]): 在当前位置i异或a[i]
查询处理：
while (cnt <= m && q[cnt].r == i): 处理所有右端点为i的查询
query(q[cnt].r)^query(q[cnt].l-1): 树状数组中区间异或和
x[q[cnt].r]^x[q[cnt].l-1]: 前缀异或和
两部分异或得到最终结果
O(n log n + m log n): 遍历数组+树状数组操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
struct node {
    int l, r, id;
    bool operator<(const node &o) const {
        return r < o.r;
    }
} q[N];

int low_bit(int x) { return x & -x; }

int n, tr[N];
void add(int i, int val) {
    for (; i <= n; i += low_bit(i))
        tr[i] ^= val;
}
int query(int i) {
    int res = 0;
    for (; i >= 1; i -= low_bit(i))
        res ^= tr[i];
    return res;
}

map<int, int> mp;
int lst[N], a[N], x[N], m, ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        x[i] = x[i-1]^a[i];
        lst[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + 1 + m);
    int cnt = 1;
    for (int i = 1; i <= n; ++i) {
        if (lst[i]) add(lst[i], a[i]);
        add(i, a[i]);
        while (cnt <= m && q[cnt].r == i) {
            ans[q[cnt].id] = query(q[cnt].r)^query(q[cnt].l-1);
            ans[q[cnt].id] ^= x[q[cnt].r]^x[q[cnt].l-1];
            cnt++;
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}