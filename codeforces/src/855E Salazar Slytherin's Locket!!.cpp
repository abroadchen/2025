//
// Created by Psy.C on 2026/9/30.
//
/**
f[b][now][res]：现在处理到第 now 位（从高位往低位），当前"数字出现奇偶性"状态为 res（res 的第 i 位为 1 表示数字 i 出现了奇数次），在非受限（!l）且非前导零（!z）‍情况下的方案数。用 b 作为第一维，因为不同进制分别记忆化。
res 上限 M=1024 = 2^10，因为只有 10 个数字位（0..9），每位的奇偶性一 bit
now	当前处理到第几位（从高到低）
l	是否"受限"（之前各位已贴着 x 的上界，l=true）
z	是否"前导零"状态（还没出现第一个非零位，z=true）
b	进制
res	当前各位数字奇偶性异或掩码
结束：now==0，若 res==0（所有数字奇偶次数都为偶数）则算 1 个合法数。
记忆化：只在非受限 && 非前导零（即该位置可以是 0..b-1 任意值）时缓存/读取 f[b][now][res]，因为受限态和前导零态因情况不同不能通用缓存
up：当前位可选最大值。l（受限）则不能超过 x 的对应位 a[now]。
若仍是前导零（z && i==0）：没产生有效数字，不翻转移位，继续前导零。
否则填入数字 i：翻转 res 第 i 位（res^(1<<i)），表示数字 i 的奇偶次数翻转
区间 [l,r] = get(r) - get(l-1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 65, M = 1024;

int f[11][N][M], a[N];
inline int dfs(int now, int l, int z, int b, int res) {
    if (!now) return !res;
    if (!l&&!z && f[b][now][res] != -1) return f[b][now][res];
    int ans = 0, up = l ? a[now] : b-1;
    for (int i = 0; i <= up; ++i) {
        if (z && !i) ans += dfs(now-1, l&&i==up, 1, b, res);
        else ans += dfs(now-1, l&&i==up, 0, b, res^(1<<i));
    }
    if (!l && !z) f[b][now][res] = ans;
    return ans;
}

int len;
inline int get(int x, int b) {
    len = 0;
    while (x) a[++len] = x%b, x/=b;
    return dfs(len, 1, 1, b, 0);
}

int q, b, l, r;
inline void solve() {
    memset(f, -1, sizeof(f));
    cin >> q;
    while (q--) {
        cin >> b >> l >> r;
        cout << get(r, b) - get(l-1, b) << '\n';
    }
}

signed main() {
    fast;
    solve();
    return 0;
}