//
// Created by Psy.C on 2026/9/28.
//
/**
N：容量上限；inf=2e9 作为正无穷初值。
a[i]：原数组。
g[cnt]：每个桶的"头元素"（桶内最小值/代表值），即各桶末尾可接的最小值记录。
cnt：当前已有桶的数量，最终 = 最长上升子序列长度 LIS。
ans[k]：第 k 个桶里按顺序收集的原始元素，用于最后输出划分。
读 n，读入数组 a[1..n]。
g[0] = inf：把"第 0 个桶"的代表值设为正无穷，作为哨兵，保证后续二分逻辑边界正确（任何数都 ≤ inf）
情况A：a[i] <= g[cnt] —— 当前元素小于等于"最后一个桶"的代表值
说明当前的 a[i] 能放到现有最后一个桶的末尾而不破坏该桶的单调性（该桶是递减/不增的）。
于是新建一个桶（++cnt），让这个桶的代表值 g[cnt] = a[i]，并把 a[i] 放进 ans[cnt]。
新增一个桶，cnt 增加，最终 cnt 会收敛到 LIS 长度。
直觉：如果 a[i] 比所有现有"桶头"都大，它必须单独开启一条新的下降链，这会使 LIS 长度增加 1
情况B：a[i] > g[cnt] —— 当前元素大于最后一个桶代表值
当前元素不能新建桶，而是要在已有的某个桶里"安放"（保证每条链仍单调）。
用二分在 g[1..cnt] 里找：第一个满足 g[mid] < a[i] 的位置（即最后一个小于 a[i] 的桶代表所在桶），把这个桶的头改为 a[i]。
g[mid] < a[i] → 说明 mid 桶的代表比 a[i] 小，a[i] 能接在该桶后，答案可能更靠左，r = mid。
否则（g[mid] >= a[i]）→ a[i] 放不进 mid 桶，往右找 l = mid+1。
二分结束后 l 指向的那个桶，g[l] = a[i] 更新其代表值，并把 a[i] push 进 ans[l]。
这里 g 数组其实始终单调"增益"排列（从大到小或递增方向），二分在 g 上找插入点，本质与标准 O(n log n) LIS 的二分逻辑一致，只是这里同时维护了每个桶的元素集合用于输出。
依次输出从 1 到 cnt 每个桶 ans[i] 里的所有元素，每个桶一行。
最终输出 cnt 条链，每条内部是递减（不增）‍序列，且桶数 cnt 就是最长上升子序列的长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, inf = 2e9;

template <typename T>
T rd() {
    T f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll a[N], g[N], cnt;
vector<ll> ans[N];
int main() {
    fast;
    ll n = rd<ll>(), i;
    for (i = 1; i <= n; ++i) a[i] = rd<ll>(); g[0] = inf;
    for (i = 1; i <= n; ++i) {
        if (a[i] <= g[cnt]) {
            g[++cnt] = a[i];
            ans[cnt].push_back(a[i]);
        } else {
            ll l = 1, r = cnt;
            while (l < r) {
                ll mid = (l + r) >> 1;
                if (g[mid] < a[i]) r = mid;
                else l = mid + 1;
            }
            g[l] = a[i];
            ans[l].push_back(a[i]);
        }
    }
    for (i = 1; i <= cnt; ++i) {
        for (ll j : ans[i]) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}