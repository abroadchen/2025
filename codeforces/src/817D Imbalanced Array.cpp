//
// Created by Psy.C on 2026/9/22.
//
/**
a[N] 存数组（下标从 1 开始）；st[N] 是单调栈，存的是下标；l[i]/r[i] 记 a[i] 作为最值时向左右可延伸的跨度；ans 累计答案。
维护一个从栈底到栈顶递增的序列：栈顶是右边能看到的小值。a[st[top]] >= a[i] 就弹出，保证栈里剩的是严格比 a[i] 小且最近的位置。
栈空 → a[i] 左边没有比它小的，l[i]=i-1（可向左延伸到下标 1）；否则最近更小者在下标 st[top]，跨度 = i - st[top] - 1（即可选 st[top]+1 .. i-1 共 i-st[top]-1 个位置）
方向反过来，求 a[i] 右边最近更小值的位置跨度。关键是这里用 > 而非 >=：左右两侧对相等元素的处理一虚一实，从而对重复值去重——保证"以某值为最小值的子数组"只被统计一次，避免重复计数
以 a[i] 为最小值的子数组个数 = (l[i]+1) × (r[i]+1)：左边可选 l[i]+1 个起点（0..l[i]），右边可选 r[i]+1 个终点，组合乘积即区间数。
因为总和 = 最大值之和 − 最小值之和，最小值部分带负号，故 ans 先减掉 a[i] 乘以其作为最小值的区间数
与最小值对称：求最大值作为最值时的跨度。左边用 <= 弹出、右边用 < 弹出（同样左右一开一合做去重）。top 在这里重新归零，复用 st/l/r 数组
每个元素作为最大值的区间数同样 = (l[i]+1)×(r[i]+1)，把 a[i] × 该数 累加进 ans（正值）。
于是 ans = Σ(a[i]×作为最大值的区间数) − Σ(a[i]×作为最小值的区间数)，正好等于所有子数组（最大值−最小值）之和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+10;
int a[N], st[N], l[N], r[N], ans;
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int top = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[st[top]] >= a[i]) top--;
        if (!top) l[i] = i - 1;
        else l[i] = i - st[top] - 1;
        st[++top] = i;
    }
    top = 0;
    for (int i = n; i >= 1; --i) {
        while (top && a[st[top]] > a[i]) top--;
        if (!top) r[i] = n - i;
        else r[i] = st[top] - i - 1;
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i) ans -= a[i]*(l[i]+1)*(r[i]+1);
    top = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[st[top]] <= a[i]) top--;
        if (!top) l[i] = i - 1;
        else l[i] = i - st[top] - 1;
        st[++top] = i;
    }
    top = 0;
    for (int i = n; i >= 1; --i) {
        while (top && a[st[top]] < a[i]) top--;
        if (!top) r[i] = n - i;
        else r[i] = st[top] - i - 1;
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i) ans += a[i]*(l[i]+1)*(r[i]+1);
    cout << ans << '\n';
    return 0;
}