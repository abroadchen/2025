//
// Created by Psy.C on 2026/9/22.
//
/**
立方体尺寸 A × B × C
每个格子 (x, y, z) 可被放置某物（如地雷/障碍消灭等）
有 n 条"攻击/约束"记录 (a, b, c)
x[a] 的含义

x[a] = min(x[a], C-c) 对每条记录 (a,b,c)。所以 x[a] = 在所有以 a 为第一坐标的记录中，C-c 的最小值。然后后缀取 min：x[i] = min(x[i], x[i+1])。

所以 x[i] = 所有满足 a ≥ i 的记录中 C-c 的最小值 = 从层 i 到 A 层中，C-c 的最小值。也就是"第 i 层及以上，z 维的某个上界的最小值"。

y[b] 的含义

同理 y[b] = 所有满足 b ≥ i 的记录中 C-c 的最小值。

cnt[a] 的含义

cnt[a] = max(cnt[a], b)：所有以 a 为第一坐标的记录中 b 的最大值。然后后缀取 max：cnt[i] = max(cnt[i], cnt[i+1])。

所以 cnt[i] = 所有 a ≥ i 的记录中 b 的最大值

这里 j 是单调递增的（双指针）。对每个 i，找到第一个 y[j] > x[i] 的位置 j（即之前 y[j] ≤ x[i] 的都跳过）。

k = max(j, cnt[i]+1)。

sum += pre[k-1] - pre[cnt[i]] + (B-k+1)*x[i]

其中 pre 是 y 的前缀和，所以 pre[k-1] - pre[cnt[i]] = Σ_{t=cnt[i]+1}^{k-1} y[t]。

所以这一项 = Σ_{t=cnt[i]+1}^{k-1} y[t] + (B-k+1)*x[i]。

这是在统计对固定 i，选择适当 z 值时可行的 (y,z) 对数。


把 x[1..A]、y[1..B] 初始化为 C（即"无约束时 z 最大可取满 C"）
x[a] = 所有"第一坐标 = a"的约束里，C-c 的最小值（z 维最紧的上界）。
y[b] = 所有"第二坐标 = b"的约束里，C-c 的最小值。
cnt[a] = 所有"第一坐标 = a"的约束里，b 的最大值
把单点极值变成后缀极值，这正是"约束沿 +x / +y 方向延伸"的体现：
x[i] = 所有 a ≥ i 的约束中 C-c 的最小值 → 在第 i 层及更靠后的 x 层，z 维被约束到的最紧上界。
cnt[i] = 所有 a ≥ i 的约束中 b 的最大值 → 第 i 层及之后，y 维会延伸到的最远 b。
y[i] = 所有 b ≥ i 的约束中 C-c 的最小值 → 第 i 行及更靠后的 y 行，z 维被约束到的最紧上界。
这样，对任意一个格子 (i, y, z)，只要它的 x≥某个约束的 a 且 y 也够大，就会被该约束影响。后缀化方便 O(1) 判断"是否受影响、z 能到多大"
pre[i] = Σ_{t=1}^{i} y[t]，用于快速求 Σ_{t=l}^{r} y[t] = pre[r]-pre[l-1]
固定 x = i 这一层，数这一层里合法的 (y, z) 对数。

对固定 i：

x[i] 是这一层 z 的上界来源之一。
j 是单调指针，指向第一个满足 y[j] > x[i] 的下标。因为 y 是（后缀 min 后）非增的，所以 j 之前都是 y[j] ≤ x[i]，之后都是 y[j] > x[i]。
cnt[i] 是这一层 y 必须越过的下界（y 至少要超过它才不识被约束直接影响）。
k = max(j, cnt[i]+1) 综合两重约束后，y 从 cnt[i]+1 到 k-1 这一段的 z 用 y[t] 本身（每行受限值较小），从 k 到 B 这一段的 z 用统一的 x[i]：

sum += [Σ_{t=cnt[i]+1}^{k-1} y[t]] + (B-k+1)*x[i]
这就是本层合法的 (y,z) 对总数。对每个 i 累加，得到三维空间里的总合法点数

把三维约束投影到二维：

按 x 分层，每一层独立统计；
每层内，y 的可行区被 cnt[i]（下界）和 x[i]/y[t]（z 上界）夹住；
z 的取值在 y 较小的一段由 y[t] 决定，在 y 较大的一段由该层统一上界 x[i] 决定；
用后缀极值处理"约束向后延伸"，用前缀和加速区间求和，用双指针保证总体 O(A+B)。
复杂度 O(A+B)，空间 O(A+B)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 5e5+2;
int n, A, B, C, x[N], y[N], cnt[N], pre[N];
signed main() {
    fast;
    cin >> n >> A >> B >> C;
    for (int i = 1; i <= A; ++i) x[i] = C;
    for (int i = 1; i <= B; ++i) y[i] = C;
    for (int i = 1, a, b, c; i <= n; ++i) {
        cin >> a >> b >> c;
        cnt[a] = max(cnt[a], b);
        x[a] = min(x[a], C-c); y[b] = min(y[b], C-c);
    }
    x[A+1] = LLONG_MAX;
    for (int i = A; i >= 1; --i) {
        cnt[i] = max(cnt[i], cnt[i+1]);
        x[i] = min(x[i], x[i+1]);
    }
    y[B+1] = LLONG_MAX;
    for (int i = B; i >= 1; --i) y[i] = min(y[i], y[i+1]);
    for (int i = 1; i <= B; ++i) pre[i] = pre[i-1] + y[i];
    int j = 1, sum = 0;
    for (int i = 1; i <= A; ++i) {
        while (j <= B && y[j] <= x[i]) ++j;
        int k = max(j, cnt[i]+1);
        sum += pre[k-1] - pre[cnt[i]] + (B-k+1)*x[i];
    }
    cout << sum;
    return 0;
}