//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
n：数的个数
a[N]：存储输入的 n 个数
cnt[N]：计数数组，cnt[i] 统计每个数值 i 出现的次数
sum：所有数的总和
dp[N][110]：DP 数组，dp[j][k] 表示用若干个数凑出总和 j，且恰好用了 k 个数的方案数
tot：统计总共出现了多少种不同的数值
ans：最终答案
设 dp[0][0] = 1，即"总和为 0、用了 0 个数"的方案数为 1（空集合，DP 的边界基础）
这是一个分组背包 / 多重背包式的 DP，把"数值 i"看作一组物品，这一组里可以选 1 到 cnt[i] 个。
j 和 k 都递减枚举，是为了避免同一组内被重复使用（保证每个项只贡献一次，防止正序滚动的错误叠加）。
l 表示"这一轮数值 i 选取 l 个"。
转移式 dp[j][k] += dp[j-i*l][k-l]：若要凑出总和 j、用 k 个数，且其中包含 l 个值为 i 的数，则剩余部分要从 dp[j-i*l][k-l]（总和 j-i*l，用了 k-l 个数）转移过来。所以是累加所有可能的取法。
最终 dp[j][k] 表示：原始序列中，能凑出总和 j、且恰好用 k 个数的总方案数（且这些数种类构成在可取的范围内）。
tot 是统计的不同数值种数。如果整个数组只有两种不同的数值，那么任意取都只会用到这两种值，符合限制，答案直接就是总数 n，输出 n 并结束程序
这里想求的是：对于每个数值 i，最多能保留多少个 i 个数（它们必须能被全部选走而不引起歧义）‍。
判断条件是 dp[i*cnt[i]][cnt[i]]，即"凑出总和 i*cnt[i]（全取 cnt[i] 个 i）、且方案数恰好为 1"。
若方案数 == 1，说明"全取 cnt[i] 个 i"是唯一的取法（其他组合无法凑出相同总和与个数），那么在最优答案中这个取法是可保留的、合法的。
若 != 1（大于 1，说明存在多种方式凑出同样总和同样个数），则可能产生歧义，需要减少取的个数 cnt[i]--，再重新判断，直到满足。
简单理解：它通过“唯一性”判断来压缩出每种数值所能合法取到的最大个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define per(i,j,k) for (int i=j; i>=k; i--)
using namespace std;

constexpr int N = 2e4+10, inf = 1e4;

int n, a[N], cnt[N], sum, dp[N][110], tot, ans;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> a[i], cnt[a[i]]++, sum += a[i];
    dp[0][0] = 1;
    rep(i,1,100) {
        if (!cnt[i]) continue;//数值 i 没出现过，跳过
        tot++;//出现了一种新的数值，tot+1
        per(j,inf,1) per(k,n,1) rep(l,1,cnt[i]) {//枚举总和 枚举用了几个数 l 枚举数值 i 取 l 个（1~cnt[i]）
            if (j < i*l) break;
            dp[j][k] += dp[j-i*l][k-l];
        }
    }
    if (tot == 2) { cout << n; return 0; }
    rep(i,1,100) {
        while (dp[i*cnt[i]][cnt[i]] != 1) cnt[i]--;
        ans = max(ans, cnt[i]);
    }
    cout << ans;
    return 0;
}