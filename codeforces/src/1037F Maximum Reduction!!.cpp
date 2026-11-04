//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
终止条件：l > r 或 l == r 时直接返回（单个元素或空区间不处理）。
取中点：q = (l+r)>>1。
预处理边界数组：
b1：从 q 向左，b1[i] = max(b1[i+1], a[i])，即位置 i 到 q 这段的后缀最大值。
b2：从 q+1 向右，b2[i] = max(b2[i-1], a[i])，即 q+1 到位置 i 的前缀最大值。
统计横跨中点的子区间（即左端在中点左侧、右端在中点右侧的区间）
固定左端点 i，其对应区间最大值至少是 b1[i]（右侧最大值不超过它的部分由 x 指针划分）。
用单调指针 x 记录：满足 b2[x+1] <= b1[i] 的最大右边界，即这些区间的最大值就是 b1[i]。
sum(i, q+1, x) 统计右端点在 [q+1, x] 范围内符合条件的区间个数，乘以 b1[i] 累加。由于 x 单调递增，总复杂度线性
对称处理：固定右端点 i，用指针 x 找左边界，sum2(i, x, q) 统计左端点在 [x, q] 的区间贡献。
注意这里用严格小于 <（与第一段的 <= 不同），目的是避免重复计数——保证每个子区间的最大值只被计一次（当最大值出现多次时归一侧）。
递归分治：dfs(l, q) 和 dfs(q+1, r) 处理不跨中点的区间

"整除分段计数"技巧：(x)/(m-1) 向下取整后作差分，可在 O(1) 时间内求出 [l, r] 中满足 下标 ≡ q (mod m-1) 之类条件的个数，避免逐点枚举
读入数组长度 n 和参数 m，读入数组，从全区间 dfs(1, n) 开始分治。
最后 (s%mod+mod)%mod 是为了把负数结果转成正数（C++ 取模可能为负）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e6+5, mod = 1e9+7;

int m;
ll sum(ll q, ll l, ll r) { return ((r-q)/(m-1) - (l-q-1)/(m-1)) % mod; }
ll sum2(ll q, ll l, ll r) { return ((q-l)/(m-1) - (q-r-1)/(m-1)) % mod; }

ll b1[N], b2[N], a[N], s;
void dfs(int l, int r) {
    if (l > r) return;
    if (l == r) return;
    int q = (l+r)>>1;
    b1[q] = a[q]; b2[q+1] = a[q+1];
    for (int i = q-1; i >= l; --i) b1[i] = max(b1[i+1], a[i]);
    for (int i = q+2; i <= r; ++i) b2[i] = max(b2[i-1], a[i]);
    int x = q;
    for (int i = q; i >= l; --i) {
        while (x+1 <= r && b2[x+1] <= b1[i]) ++x;
        s = (s + b1[i]*sum(i,q+1,x)%mod) % mod;
    }
    x = q+1;
    for (int i = q+1; i <= r; ++i) {
        while (x-1 >= l && b1[x-1] < b2[i]) --x;
        s = (s + b2[i]*sum2(i,x,q)%mod) % mod;
    }
    dfs(l, q); dfs(q+1, r);
}

int n;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dfs(1,n);
    cout << (s%mod+mod)%mod;
    return 0;
}