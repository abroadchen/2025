//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
a[N]：原数组（1-based）。
lst[N]：lst[i] = 从位置 i 开始，第一个不是 1 的位置（或 n+1）。
l, r：左、右指针
从右往左扫：

lst[n+1] = n+1：哨兵。
若 a[i]==1：lst[i] = lst[i+1]（延续右侧最近的非 1 位置）。
否则 a[i]!=1：lst[i] = i（自己就是非 1）。
效果：lst[i] 能直接告诉我们"从 i 开始连续多少个 1，然后在哪个位置遇到第一个非 1"。这样遇到一段 1 就不用逐一扫描
对每个左端点 l，右指针 r 从 l 向右扩展，维护：

s：区间 [l, r-1]（已扫部分）的乘积。
sum：区间 [l, r-1] 的和。
情况一：a[r] 不是 1（正常元素）
先判断防溢出：若 s > inf/a[r] 则停止（避免 s*a[r] 溢出 long long）。
否则把 a[r] 乘进 s、加进 sum。
检查当前区间 [l, r] 是否满足 s == sum*k，满足则 cnt++。
情况二：a[r] == 1（跳过连续一段 1）
当右指针落在 1 上时，lst[r] 到 r 之间原是一段"系数为 1"的区域。因为我们希望最终某个子区间 [l, r']（r' 落在这一段 1 里）满足条件：

区间 [l, r'] 的乘积仍为 s（乘 1 不改变乘积）。
区间 [l, r'] 的和为 sum + (r'−r+1)（每多含一个 1，和 +1）。
条件 s == k·(sum + t)，其中 t 为含 1 的个数（1 ≤ t ≤ lst[r]−r）。整理得：

t = s/k − sum
因此若 s % k == 0（保证 s 能被 k 整除），且

1 ≤ s/k − sum ≤ lst[r] − r
（即 t 落在可选的 1 的数量范围内），则这段能有 cnt 种满足条件的右端点位置 → 计数 +1。

然后：

sum += lst[r] - r;   // 把这段 1 全部加进 sum
r = lst[r];          // 右指针跳到最近的非 1 位置
lst[r] - r 就是这段连续 1 的个数。把整段都并入 sum 后跳到下一个非 1。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; i++)
#define per(i,n) for (i = n; i >= 1; i--)
#define int long long
using namespace std;

constexpr int N = 2e5+5, inf = 2e18;

int n, k, i, a[N], lst[N], l, r;
signed main() {
    fast;
    cin >> n >> k;
    rep(i,n) cin >> a[i];
    lst[n+1] = n+1;
    per(i,n) {
        if (a[i] == 1) lst[i] = lst[i+1];
        else lst[i] = i;
    }
    int cnt = 0;
    rep(l,n) {
        int s = 1, sum = 0;
        for (r = l; r <= n; ) {
            if (a[r] != 1) {
                if (s > inf/a[r]) break;
                s *= a[r]; sum += a[r];
                if (s == sum*k) cnt++;
                r++;
            } else {
                if (s%k == 0 && s/k >= 1+sum && s/k <= sum+lst[r]-r) cnt++;
                sum += lst[r] - r;
                r = lst[r];
            }
        }
    }
    cout << cnt;
    return 0;
}