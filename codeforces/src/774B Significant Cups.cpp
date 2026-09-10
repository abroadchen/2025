//
// Created by Psy.C on 2026/9/10.
//
/**
每个物品有 d（耗时/费用）和 w（价值/权重）
排序比较器：按价值 w 降序，价值相同则按耗时 d 升序
n1, n2 两组物品数，m 总限制。
da/wa：A 组排序后 d/w 的前缀和数组；db/wb 同理为 B 组

读入两组物品，各自按 cmp 排序（价值降序、耗时升序）
对 A、B 分别做前缀和：da[i] = 取 A 前 i 个的总耗时，wa[i] = 取 A 前 i 个的总价值；B 同理
外层枚举 A 组取多少个（i 个，总耗时 da[i]）。
内层对 B 组二分：在 [l=1, r=n2] 里找一个最大的 mid，使得 da[i]+db[mid] <= m（即 B 组还能取 mid 个）。循环用 while (r-l>1) + mid 逼近，这是通用的"找最大可行下标"二分写法。
找到后，用 l 和 r 两个候选（因为二分结束时 l、r 相邻，取合法者）计算总价值 wa[i]+wb[l] / wa[i]+wb[r]，与 ans 取 max。
最终输出 ans，即最大总价值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

struct Node { int d, w; } a[N], b[N];

bool cmp(Node x, Node y) {
    if (x.w != y.w) return x.w > y.w;
    return x.d < y.d;
}

int n1, n2, m;
ll da[N], wa[N], db[N], wb[N];
int main() {
    fast;
    cin >> n1 >> n2 >> m;
    for (int i = 1; i <= n1; ++i) cin >> a[i].w >> a[i].d;
    for (int i = 1; i <= n2; ++i) cin >> b[i].w >> b[i].d;
    sort(a + 1, a + n1 + 1, cmp);
    sort(b + 1, b + n2 + 1, cmp);
    for (int i = 1; i <= n1; ++i) {
        da[i] = da[i-1] + a[i].d;
        wa[i] = wa[i-1] + a[i].w;
    }
    for (int i = 1; i <= n2; ++i) {
        db[i] = db[i-1] + b[i].d;
        wb[i] = wb[i-1] + b[i].w;
    }
    ll ans = 0;
    for (int i = 1; i <= n1; ++i) {
        int l = 1, r = n2;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (da[i] + db[mid] <= m) l = mid;
            else r = mid - 1;
        }
        if (da[i] + db[r] <= m)
            ans = max(wa[i]+wb[r], ans);
        if (da[i] + db[l] <= m)
            ans = max(wa[i]+wb[l], ans);
    }
    cout << ans << '\n';
    return 0;
}