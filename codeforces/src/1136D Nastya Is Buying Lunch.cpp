//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
a[]：主序列（长度 n）。
v[i]：记录所有需要 i 作为前置的"客户"（v[y].push_back(x) 表示 y 被 x 需要）。
cnt[]：统计"当前仍被需要的值"的累计需求数。
ans：答案（已通过的合法前缀长度）
读序列 a；再读 m 条依赖 x y，表示「y 需要 x」，所以把 x 存入 v[y]（y 的前置依赖 x）
对序列最后一个值 a[n]，它对应的依赖 v[a[n]] 中的每个 x，令 cnt[x]++。即"当前的需求"都来自末尾元素
倒序遍历 i = n-1 … 1：

判断条件 n-i-ans == cnt[a[i]]：
n-i：从 i 到末尾的总跨度。
ans：已确认通过的合法元素数。
二者之差 = 当前还有几个未处理元素。
若它等于 cnt[a[i]]（即"需要 a[i] 的次数恰好等于剩余未处理数"），则说明 a[i] 是"必须"保留的（每个未处理者都需要它），此时 ans++。
否则（还有富余/多余），把 a[i] 自身的依赖 v[a[i]] 全部累计进 cnt（因为这些元素现在也有了需求），供后续判断
输出能"安全通过"的最大长度 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 3e5+5;
int n, m, a[N], cnt[N], ans;
vector<int> v[N];
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int x, y;
    for (int i = 0; i < m; i++) { cin >> x >> y; v[y].push_back(x); }
    for (int i : v[a[n]]) cnt[i]++;
    for (int i = n-1; i >= 1; i--) {
        if (n-i-ans == cnt[a[i]]) ans++;
        else { for (int j : v[a[i]]) cnt[j]++; }
    }
    cout << ans << '\n';
    return 0;
}