//
// Created by Psy.C on 2026/9/20.
//
/**
n：朋友个数
f：可以使用的"讲题/翻倍"次数上限
k[i]：第 i 个朋友已懂的题数
l[i]：第 i 个朋友总题数（已懂+未懂）
a[]：所有"翻倍带来的收益"记录数组
cnt：a 数组当前元素个数
情况 1：k[i] == 0

使用一次翻倍机会：min(0*2, l) = 0，毫无收益。
{} 空操作 → 直接跳过。这类朋友毫无价值，不占用 f、不加 ans。
情况 2：k[i] >= l[i]

已懂题数已到达瓶颈（翻倍只会到总题数 l，不会比 l 多）。
其实这里由于 k>=l，能贡献的就是 l（封顶总题数）。
直接 ans += l[i]，不用翻倍（即使翻倍收益也是 0，因为 min(2k,l)-k = l-k = 0，只是当前没写 "else if" 分支而是单独处理）。
注意：这里 k[i] >= l[i] 时 ans += l[i] 而不是 += k[i]，是因为此时 k≥l 意味着已懂题数 ≥ 总题数（不合理但题目允许），能记账的封顶是 l。
情况 3：k[i] < l[i]（有翻倍空间）

先必然记下基础已懂题数：ans += k[i]。

然后记录"用一次翻倍机会能多赚多少"：
翻倍后已懂数 = min(2·k, l)（封顶在总题数 l），收益 = 翻倍后 − 翻倍前 = min(2k, l) - k。

这一步是贪心的核心：把每个朋友的"翻倍增益"单独存进数组 a，稍后按增益从大到小分配 f 次机会
把收益数组 a 从小到大排序。
从最大收益（i = cnt-1）开始倒序遍历，每次用一次的翻倍机会，把该收益加进 ans，f--。
直到：f 用完（f==0 break）或收益数组遍历完。
这是标准贪心：总是把有限的 f 次机会给"增益最大"的朋友，从而最大化总收益。因为每个朋友"翻倍"只算一次（每朋友最多翻倍一次），而所有朋友的增益互相独立，所以只需取前 f 个最大增益即可——排序 + 取前 f 个，O(n log n)。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10;

int n, f, k[N], l[N], a[N];
int main() {
    fast;
    cin >> n >> f;
    ll ans = 0; int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> k[i] >> l[i];
        if (k[i] == 0) {}
        else if (k[i] >= l[i]) ans += l[i];
        else {
            ans += k[i];
            a[cnt++] = min(k[i]*2, l[i]) - k[i];
        }
    }
    sort(a, a + cnt);
    for (int i = cnt-1; i >= 0; --i) {
        if (f == 0) break;
        ans += a[i];
        f--;
    }
    cout << ans << '\n';
    return 0;
}