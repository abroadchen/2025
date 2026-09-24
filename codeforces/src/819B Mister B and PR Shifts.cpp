//
// Created by Psy.C on 2026/9/23.
//
/**
w 开成 2n 大小，是为了把环复制成两条（w[i+n] = w[i]），方便处理循环旋转。
d[N][2]：差分数组，两维分别记录"某种变化量"的增量（用于后面差分求 c1、c2）
读入 n 个数，并复制一份放到 [n+1, 2n]，得到长度为 2n 的数组，模拟环形
对每个位置 i，在区间 [i, ?] 上做差分标记。这一步是预处理"每次旋转后 c1（或 c2）变化多少"的差分。
具体含义：w[i] > i 与 w[i] <= i 两条分支对应环形结构中"数字绕一圈到达目标位置"时 c1/c2 变化的分段点。这些 d 数组用于 O(1) 更新转轮后的 c1、c2
ans = 初始时所有 abs(w[i]-i) 之和。
c1 = 满足 w[i] < i 的元素个数；c2 = 满足 w[i] >= i 的元素个数（注意 c1 + c2 = n）
循环 i = 1..n-1 代表旋转 i 个单位。
t 维护当前旋转状态下的总代价。
每次旋转通过递推式 t = t - c1 + c2 - 1（加上差分修正）从上一状态快速得到新代价，O(1) 而非 O(n) 重算。
K 记录第一次达到最小值的旋转次数（if (t < ans) K = i 只在严格小于时更新，即取"最早/最小"达到最优的旋转次数）
输出最小代价 ans 和 n - K。
n - K 是把"旋转 K 次的代价"换算成题目要求的另一种形式（比如题目问的是"还需调整的位置数"或反方向旋转次数）。具体 n-K 的含义取决于原题——K 是旋转次数，n-K 可能是反向等的补数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ck_min(x,y) (x=min(x,y))
using namespace std;

constexpr int N = 2e6+1100;

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int w[N<<1], d[N][2];
signed main() {
    fast;
    int n = read();
    for (int i = 1; i <= n; ++i) w[i+n] = w[i] = read();
    for (int i = 1; i <= n; ++i) {
        d[i][0]++, d[i][1]--;
        if (w[i] > i) d[i+n-w[i]][0]--, d[i+n-w[i]][1]++;
        else d[i-w[i]][0]--, d[i-w[i]][1]++;
    }
    int c1(0), c2(0), ans(0);
    for (int i = 1; i <= n; ++i) {
        ans += abs(w[i]-i);
        c1 += w[i] < i; c2 += w[i] >= i;
    }
    int t = ans, K = n;
    for (int i = 1; i < n; ++i) {
        t -= abs(w[i]-1) - abs(w[i]-n);
        t -= c1, t += c2, t--;
        c1 += d[i][0], c2 += d[i][1];
        if (t < ans) K = i;
        ck_min(ans, t);
    }
    cout << ans << ' ' << n-K;
    return 0;
}