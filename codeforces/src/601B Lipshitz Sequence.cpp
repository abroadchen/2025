//
// Created by Psy.C on 2026/3/21.
//
/**
n, q: 数组长度和查询次数
a[N]: 原始数组
b[N]: 相邻元素差值的绝对值数组
L[N], R[N]: 每个位置左边和右边第一个更大元素的位置
l, r: 查询区间
x, y: 临时变量
更新n为差值数组长度
使用单调递减栈找到每个位置左边第一个更大的元素位置
L[i]表示b[i]左边第一个更大值的位置
清空栈后，从右往左遍历
找到每个位置右边第一个严格大于当前值的位置
注意这里使用<而不是<=，避免重复计算
对每个查询区间[l, r]
对于每个位置i，计算它在子区间中的贡献：
x = max(L[i], l-1): 左边界限制在[l, i]范围内
y = min(R[i], r): 右边界限制在[i, r]范围内
(y-i): 右端点可选的数量
(i-x): 左端点可选的数量
b[i]*(y-i)*(i-x): b[i]作为最大值的子区间总贡献

预处理：O(n)
每次查询：O(r-l+1)，最坏情况O(n)
总体：O(n + q×n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
int n, q, a[N], b[N], L[N], R[N], l, r, x, y;
stack<int> st;
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) b[i] = abs(a[i+1] - a[i]);
    n--;
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && b[st.top()] <= b[i]) st.pop();
        L[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
    while (st.size()) st.pop();
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && b[st.top()] < b[i]) st.pop();
        R[i] = st.empty() ? n + 1 : st.top();
        st.push(i);
    }
    ll ans;
    while (q--) {
        ans = 0; cin >> l >> r;
        for (int i = l; i <= r-1; ++i) {
            x = max(L[i], l - 1); y = min(R[i], r);
            ans += 1ll*b[i]*(y-i)*(i-x);
        }
        cout << ans << '\n';
    }
    return 0;
}