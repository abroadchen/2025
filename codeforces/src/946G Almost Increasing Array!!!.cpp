//
// Created by Psy.C on 2026/10/18.
//
/**
tr[0]：存 f[i][0]（未删过元素的最长合法前缀来到 i 的长度）。
tr[1]：存 f[i][1]（已删 1 个元素的最长合法前缀来到 i 的长度）。
tr[2]：用于计算"删掉一个元素后，还能再往前跳到更早位置"所需的中间量——存 f[i-1][0]（用来支持"跳过 1 个位置后接上前一个合法位"）。
每个 BIT 存的是"以该离散值为末尾的最长长度"的前缀最大值，getsum 取 ≤ 该值 的最大值，正是非递减 DP 需要的
把 b[i] 和 b[i]+1 一起离散化（因为 f[i][1] 的跨跳转移要查 b[i]+1）
f[i][0]（未删）‍：从 tr[0]（也是未删状态）里选 ≤ b[i] 的最长前身 + 1。这是标准的"非递减 LIS"在未删路径上的表达。
f[i][1]（已删 1 个）‍：两种来源取最大——
之前已经删过 1 个的状态 tr[1] 直接接上 i（仍保持已删 1 个）；
或者在 i 这个位置用掉这一次删除——即跳过 i-1，从 tr[2]（存的历史 f[j][0]，j ≤ i-2）里取 ≤ b[i]+1 的最长值再 +1。这里用 b[i]+1 是因为"删掉 i-1 后，i 可以直接与 j (j≤i-2) 比较"，允许 i 的值比前一个合法位大 1，语义上相当于跳过的那个元素被"吞掉"了一个可比较单位
ans = 所有状态里能达到的最大合法长度。
输出 max(n-1-ans, 0)：这是题目要求的答案口径（n-1 是因为题面允许"至多删 2 个"但答案用 n-1-ans 形式表达最少需删/改的次数，-1 为题面常数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define low_bit(x) (x&(-x))
#define ll long long
using namespace std;

constexpr int N = 2e5+10, M = 4e5+10;

struct node {
    ll c[M];
    void add(ll n, ll x, ll val) {
        for (ll i = x; i <= n; i += low_bit(i))
            c[i] = max(c[i], val);
    }
    ll getsum(ll x) {
        ll ans = 0;
        for (ll i = x; i >= 1; i -= low_bit(i))
            ans = max(ans, c[i]);
        return ans;
    }
} tr[3];

ll n, a[N], b[N], c[M], f[N][2], ans;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) {
        cin >> a[i]; b[i] = a[i] - i;
        c[2*i-1] = b[i];
        c[2*i] = b[i] + 1;
    }
    sort(c+1, c+2*n+1);
    c[0] = unique(c+1, c+2*n+1) - (c+1);
    rep(i,1,n) {
        f[i][0] = tr[0].getsum(lower_bound(c+1, c+1+c[0], b[i]) - c) + 1;
        f[i][1] = tr[1].getsum(lower_bound(c+1, c+1+c[0], b[i]) - c);
        f[i][1] += f[i][1] != 0;
        if (i-2 >= 1) f[i][1] = max(f[i][1],
            tr[2].getsum(lower_bound(c+1, c+1+c[0], b[i]+1) - c)+1);
        tr[0].add(c[0], lower_bound(c+1, c+1+c[0], b[i])-c, f[i][0]);
        tr[1].add(c[0], lower_bound(c+1, c+1+c[0], b[i])-c, f[i][1]);
        if (i-1 >= 1) tr[2].add(c[0], lower_bound(c+1, c+1+c[0], b[i-1])-c, f[i-1][0]);
    }
    rep(i,1,n) ans = max(ans, max(f[i][0], f[i][1]));
    cout << max(n-1-ans, 0ll) << '\n';
    return 0;
}