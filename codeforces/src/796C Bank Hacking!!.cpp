//
// Created by Psy.C on 2026/9/17.
//
/**
读 n。
读每个节点初始权值 a[i]。
读 n-1 条边，用 邻接表 q 存无向树
找全树中最大值 m1 及其个数 n1，次大值 m2 及其个数 n2：
若 a[i] > m1：更新 m1 为新最大值，旧 m1 变次大 m2；重置计数。
若 a[i] == m1：最大值个数 n1++。
否则（a[i] < m1）：与次大 m2 比较，更新 m2 及其计数 n2。
结果：m1=全局最大权值，n1=有多少个节点取到 m1；m2=全局次大，n2=取到 m2 的个数
对每个候选中心节点 i：

c = a[i]：先把中心自己的权值作为当前候选"最大值"（它会被 +1，待会 max 处理）。
t1 = n1, t2 = n2：拷贝全局最大/次大计数。
若中心自己等于 m1/m2，则对应计数减 1（因为它被"消费"为邻居之一，不能计入"外部未 +1 的最大值"）。
遍历 i 的所有邻居 j：
c = max(c, a[j]+1)：邻居会被 +1，用 a[j]+1 更新候选最大值。
邻居若是全局最大/次大，同样对应计数 t1/t2 减 1（被 +1 消费了）。
处理未被 +1 的最大/次大节点：
若 t1 > 0：仍存在不是中心也不是其邻居的全局最大节点，它没被 +1，但中心操作会让"最大值的最大值"整体 +1？这里用 m1+2——即这类外部最大值节点实际会变成 m1+2（因为中心 +1 会让它相对再 +1？代码用 +2）。c=max(c, m1+2)。
同理 t2>0 时用 m2+2。
用当前中心的候选最大值 c 更新全局最优 ans = min(ans, c)。
这里的 +1/+2 语义来自对"中心及邻居 +1 之后，其余最大值节点会额外再 +1"的推导（即中心节点被 +1 后，若它不是最大者，最大者会相对被 +1……这类题常见的 trick：最大值不在中心/邻居时，会多 +1，共 +2）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;
constexpr ll inf = 1e10;
ll a[N];
vector<ll> q[N];
int main() {
    fast;
    ll n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        q[x].push_back(y); q[y].push_back(x);
    }
    ll m1 = -inf, m2 = -(inf+1), n1(0), n2(0);
    for (int i = 1; i <= n; ++i) {
        if (a[i] > m1) {
            m2 = m1; n2 = n1; m1 = a[i]; n1 = 1;
        }
        else if (a[i] == m1) n1++;
        else {
            if (a[i] > m2) { n2 = 1; m2 = a[i]; }
            else if (a[i] == m2) n2++;
        }
    }
    ll c, t1, t2, ans = inf+1;
    for (int i = 1; i <= n; ++i) {
        c = a[i]; t1 = n1; t2 = n2;
        if (c == m1) t1--;
        if (c == m2) t2--;
        for (long long j : q[i]) {
            c = max(c, a[j]+1);
            if (a[j] == m1) t1--;
            if (a[j] == m2) t2--;
        }
        if (t1 > 0) c = max(c, m1+2);
        if (t2 > 0) c = max(c, m2+2);
        ans = min(ans, c);
    }
    cout << ans;
    return 0;
}