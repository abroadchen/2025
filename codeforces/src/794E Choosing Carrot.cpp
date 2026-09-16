//
// Created by Psy.C on 2026/9/16.
//
/**
对区间 [l, r]，假装"最大值出现在中点附近"，按区间长度奇偶返回：

mid = (l+r)>>1：中间下标。
若区间长度为偶数（(r-l)&1==1，元素个数为偶数）：返回 max(a[mid], a[mid+1])——两中位元素取大。
若区间长度为奇数（元素个数为奇数）：返回 max( min(a[mid-1],a[mid]), min(a[mid],a[mid+1]) )——取"三分取中"的两组相邻对的最小值里再取大的。
这其实是"在没真正扫描全区间的情况下，用中点邻域估计区间内某个特征值"。它成立的前提是：数组经过某种重排/构造，使得真正的答案必然落在中点附近这几个位置上（这就是这题的精髓所在，也是为什么它是最优 O(n) 解）

第 0 个答案 ans[0] = get(1, n)：整段区间 [1,n] 的结果。

第 1 个答案 ans[1] = max( get(1,n-1), get(2,n) )：去头或去尾两种删除（删掉 1 个元素）得到的两种结果取大。

递推（i=2..n-2）
get(1, n-i)：删掉末尾 i 个元素后的区间。
get(i+1, n)：删掉开头 i 个元素后的区间。
与 ans[i-2] 取 max——这里形成隔一步递推（步长 2），对应"删除 i 个元素"的情况与"删除 i-2 个元素"的情况之间的转移。
结果存到 ans[i]，表示"删掉 i 个元素"时能得到的最优值
对 i = 0..n-2 输出 ans[i]（对应删 i 个元素最优值）。
最后一个位置（i = n-1）输出全局最大值 mx——因为删掉 n-1 个元素只剩 1 个元素，答案自然是全局最大那个。这是边界特判
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 3e5+5;

int a[N];
inline int get(int l, int r) {
    int mid = (l+r)>>1;
    if ((r-l)&1) return max(a[mid], a[mid+1]);
    return max(min(a[mid-1], a[mid]), min(a[mid], a[mid+1]));
}

int mx, ans[N];
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], mx = max(mx, a[i]);
    ans[0] = get(1, n);
    ans[1] = max(get(1, n-1), get(2, n));
    for (int i = 2; i < n-1; ++i)
        ans[i] = max(ans[i-2], max(get(1, n-i), get(i+1, n)));
    for (int i = 0; i < n; ++i)
        cout << (i < (n-1) ? ans[i] : mx) << ' ';
    return 0;
}