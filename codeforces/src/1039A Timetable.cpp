//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
若 x[i] < x[i-1]：LIS 长度递减——非法，因为 LIS 长度必然非降。
若 x[i] < i：x[i] 表示"以 i 结尾的最长递增子序列长度"，最长为 i，而至少为 1……这里条件 x[i] < i 其实是在判断一种必须满足的下界关系（结合题目具体约束，LIS 长度不可能超过位置 i——故 x[i]>i 非法）。
任一不满足即无解
把原数组按 x 的取值分成若干连续段，每段内 x 都相等，逐段贪心构造 b
对段内每个位置 k：
若 x[k] > k：该位置的 LIS 长度大于位置号。此时无法在自身前缀中形成这么长的递增长度，只能借助"下一个候选值"，设为 a[k+1]+m（取后一元素的上界）。
否则（x[k] ≤ k）：b[k] = max(b[k-1]+1, a[k]+m)——取"前一个 b 严格 +1（保证递增）"与"当前元素可选上界"的较大者。
这样保证 b 严格递增，且每个 b[k] 落在允许的选择范围内（上层边界 a[k]+m 或后撤边界）
段尾 j-1 需要满足两个条件：

x[j-1] == j-1：段尾位置的 LIS 长度必须等于其位置号（即该前缀 LIS 长度恰好等于下标，这是可行性的必要边界）；
若后面还有元素（j-1 < n），要求 b[j-1] < a[j]+m（当前段尾 b 值严格小于下一元素可选上界，保证能继续递增构造）。
任一不满足 -> 无解 No
全部满足则输出 Yes 和构造好的 b 数组
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

ll n, m, a[N], b[N];
int x[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> x[i];
    for (int i = 2; i <= n; i++)
        if (x[i] < x[i-1] || x[i] < i) {
            cout << "No\n";
            return 0;
        }
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j <= n && x[j] == x[i]) j++;
        for (int k = i; k < j; k++) {
            if (x[k] > k) b[k] = a[k+1] + m;
            else b[k] = max(b[k-1]+1, a[k]+m);
        }
        if (x[j-1] != j-1 || (j-1 < n && b[j-1] >= a[j]+m)) {
            cout << "No\n";
            return 0;
        }
        i = j;
    }
    cout << "Yes\n";
    for (i = 1; i <= n; i++) cout << b[i] << (i==n?'\n':' ');
    return 0;
}