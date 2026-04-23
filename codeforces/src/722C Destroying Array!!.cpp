//
// Created by Psy.C on 2026/4/23.
//
/**
n：数组长度
a[N]：输入数组
f[N]：前缀和数组
q1：最大堆，存储所有区间的最大前缀和
q2：最大堆，存储需要删除的区间和
st：有序集合，存储已删除的位置

将整个数组的和 f[n] 和0压入q1
在集合中插入0
循环n次，每次处理一个删除位置x
st.lower_bound(x)：找到集合中第一个大于等于x的位置
r：右边界（当前x右边最近的已删除位置-1，如果没有则为n）
如果 r != x，将区间 [x+1, r] 的和压入q1
l：左边界（当前x左边最近的已删除位置+1，如果没有则为1）
如果 l != x，将区间 [l, x-1] 的和压入q1
将区间 [l, r] 的和（删除x之前的完整区间）压入q2（待删除）
删除q1和q2中相同的顶部元素（延迟删除机制）
输出当前最大子段和（q1的顶部）
将x插入已删除位置集合
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7;
ll n, a[N], f[N];
priority_queue<ll> q1, q2;
set<int> st;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        f[i] = f[i-1] + a[i];
    }
    q1.push(f[n]); q1.push(0); st.insert(0);
    for (int i = 1, x, l, r; i <= n; ++i) {
        cin >> x;
        auto it = st.lower_bound(x);
        if (it != st.end()) r = *it - 1; else r = n;
        if (r != x) q1.push(f[r] - f[x]);
        if (it != st.begin()) {
            --it;
            l = *it + 1;
        } else l = 1;
        if (l != x) q1.push(f[x-1] - f[l-1]);
        q2.push(f[r] - f[l-1]);
        while (!q2.empty() && !q1.empty() && q1.top() == q2.top()) {
            q1.pop(); q2.pop();
        }
        cout << q1.top() << '\n';
        st.insert(x);
    }
    return 0;
}