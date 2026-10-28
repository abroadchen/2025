//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
low_bit(x)：取 x 最低位的 1（x & -x），树状数组核心操作。
sum(x)：查询前缀和（[1, x] 的累加），用于单点更新、前缀查询。
add(x, y)：对位置 x 增加 y，向上更新。边界是 n<<1|1（即 2n+1），因为后面用到的下标范围需要覆盖到 [-n, n] 偏移后的范围
o < x → y -= 1（小于 x 记 -1）；
o >= x → y += 1（大于等于 x 记 +1）。
这样 y 就是基于阈值 x 的 ±1 前缀和：pre[i] = (≥x 的个数) - (<x 的个数)。

为什么能换算成"中位数 ≥ x"：对一个子数组 [l+1, r]，其内部这种"高度差"=pre[r]-pre[l] ≥ 0 ⟺ 该子数组中 ≥x 的个数 ≥ <x 的个数 ⟺ 中位数 ≥ x（对"上中位"或混合定义成立）。更精确地，用累积计数：

ans += sum(y+n, tr)：在索引为 y+n 的前缀中查询 ≤ y 的前缀和个数。因为树状数组存的是"已出现的前缀和值"的频次（索引 = 前缀和 + n 的偏移，把可能为负的 pre 映射到正索引）。

内部语义：sum(y+n) = 前面出现过、且值 ≤ y 的前缀和个数。对每个当前前缀 y，前面所有 ≤ y 的前缀 pre[j] 都满足 y - pre[j] ≥ 0，即 pre[j] ≤ y → 子数组 (j, i] 的中位数 ≥ x。所以累加这些个数就得到"以 i 为右端点、中位数 ≥ x 的子数组数量"

add(n+1, 1, tr) 先放"空前缀 0"：对应索引 0+n+1 = n+1。也就是空前缀存在，且它排在位置 n+1。这样 pre[0]=0，而前缀和最小可到 -n（全为 -1），最大 n（全为 +1）。
每次把当前 y 插入 add(y+n+1, 1)，即索引 y+n+1。
查询 sum(y+n) 是 [1, y+n] 前缀，也就是"≤ y+n 且 ≥ 最小编号"的所有已插入前缀 = pre[j] + n + 1 ≤ y+n ⟺ pre[j] ≤ y-1？
这里要小心对齐。让我重新对齐索引口径：

空前缀 pre=0 插入到索引 n+1。即索引 = pre + (n+1)？那 pre=0 → 索引 n+1 ✓。
当前 y 查询 sum(y+n) 查询的是 pre + (n+1) ≤ y + n ⟺ pre ≤ y-1。
当前 y 插入 add(y+n+1) 索引 = y+n+1 = y + (n+1)，即 pre=y 对应索引 y+n+1 ✓（与 pre=0→n+1 一致）。
所以查询 sum(y+n) 统计的是所有 pre ≤ y-1 的前缀个数。

于是子数组 (j,i] 满足 pre[i] - pre[j] ≥ 1，即 pre[j] ≤ pre[i]-1。这意味着我们统计的是 pre[i] - pre[j] ≥ 1（差 ≥1）的情形。

这与"中位数 ≥ K"的精确判定有关：当用 ±1（<K→-1, ≥K→+1）时，子数组内 ≥K 数量 − <K 数量 ≥ 1 ⟺ 中位数 ≥ K（上中位数）。所以这里统计"差 ≥ 1"完全对应"中位数 ≥ x"。✅
solve(x)：中位数 ≥ x 的子数组数。
solve(x+1)：中位数 ≥ x+1 的子数组数。
两者之差 = 中位数正好 = x 的子数组数（因为中位数是整数，≥x 且 <x+1 ⟺ =x）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5, M = 4e5+5;

int low_bit(int x) { return x & (-x); }
int sum(int x, int sz[]) {
    int ans = 0;
    for (int i = x; i; i -= low_bit(i)) ans += sz[i];
    return ans;
}

int n;
void add(int x, int y, int sz[]) {
    for (int i = x; i <= (n<<1|1); i += low_bit(i))
        sz[i] += y;
}

int tr[M], a[N];
int solve(int x) {
    int ans = 0, y = 0, i;
    memset(tr, 0, sizeof(tr));
    add(n+1, 1, tr);//在"空前缀和=0"对应的索引处插入1
    rep(i,n) {
        int o = a[i];
        y += o < x ? -1 : 1;
        ans += sum(y+n, tr);
        add(y+n+1, 1, tr);
    }
    return ans;
}

int x, i;
signed main() {
    fast;
    cin >> n >> x;
    rep(i,n) cin >> a[i];
    cout << solve(x) - solve(x+1);
    return 0;
}