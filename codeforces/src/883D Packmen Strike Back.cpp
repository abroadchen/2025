//
// Created by Psy.C on 2026/10/7.
//
/**
一条长度为 n 的线，字符串 s，含 P（巡逻/采集者，可移动）和 *（目标/蘑菇，需要被接管）。
目标是所有 * 都被 P 覆盖。
d = 所有 P 的个数，p[i] = 第 i 个 P 的位置（下标 0..n-1）。
pn[i] = 前缀中 * 的个数（前缀和，用于判断某位置前有多少个 *，进而判断"某位置是否已覆盖所有前面需要的 *"）。
lst = 最后一个 * 的位置。
多个人 P，每个人可以在其被覆盖的范围内移动去收集 *。问题：在最小化最大用时（即每个人能覆盖的最大距离 k）下，能否收集完所有 *，并求这个最小 k。

ok(k) 判定在"每步最多走 k 的距离"（或"每个 P 的任务极限"）下能否成功。最后输出覆盖的总蘑菇数 pn[n-1] 和最小极限 l
cnt=0：没有 P，无蘑菇可收（输出 0 0）。
cnt=1：只有一个 P，直接贪心计算左右两侧能收到多少蘑菇，取多的一侧，若相等取用时短的。这是特判，因为一个 P 只能往一个方向走到底。
cnt>1：跑二分 + DP
单个人只能选一个方向走到底（不能回头），所以取蘑菇多的一侧；若两侧等量，则取需走距离更短的一侧
在可行域上二分最小 k（在 bool ok(mid) 性质单调下：k 越大越容易成功）。最终 l 是最小的可行 k。
输出收集总数 pn[n-1] 和最小 k
dp[i] 语义：第 i 个 P（位置 p[i]），在它完成自己职责后，向右最多能覆盖到哪个位置（即最右能推进到的下标
解释每一条转移（都是条件判断当前 P 的前缀是否已无待收蘑菇，然后推进 dp 值）：

转移 1：当前 P p[i] 向右走 k，最右覆盖到 p[i]+k。前提：之前所有蘑菇（到 p[i]-1 为止）都已被前面的 P 覆盖——条件是 dp[i-1] >= p[i]-1（上一个 P 覆盖位超过 p[i]-1），或它们前缀蘑菇数相等 pn[dp[i-1]] == pn[p[i]]（即 dp[i-1] 到 p[i] 之间没有多余蘑菇，说明 p[i] 之前已清空）。
转移 2：当前 P 向左走（覆盖 p[i]-k-1 到 p[i]），dp 延伸到 p[i]。前提：所有 p[i]-k-1 之前的蘑菇已被覆盖。
转移 3：跳过中间（涉及 i-2 与 i-1 的组合），允许用 p[i-1]+k 作为覆盖延伸，处理更复杂的覆盖模式。
if (dp[i] < p[i]) return false：如果第 i 个 P 连自己位置 p[i] 都无法确保前面蘑菇被清空（dp[i] 没超过 p[i] 前的待处理范围），则失败。

最后检查最后一个 *（lst）是否被最后一个 P 覆盖到（lst <= dp[d]）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int dp[N], d, p[N], pn[N], lst;
bool ok(int k) {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= d; ++i) {
        //转移 1：当前 P 直接向右覆盖 p[i]+k
        //"上一个 P 已覆盖到 p[i]-1"（即 p[i] 之前的位置已无未收蘑菇）
        if ((i-1==0?-1:dp[i-1]) >= p[i]-1 ||
            (i-1==0?0:pn[dp[i-1]]) == pn[p[i]])//前一个 P 覆盖范围内已覆盖完直到 p 的所有 '*'（前缀相等判断）
            dp[i] = max(dp[i], p[i]+k);
        //转移 2：当前 P 向左覆盖到 p[i]-k-1
        if ((i-1==0?-1:dp[i-1]) >= p[i]-k-1 ||
            (i-1==0?0:pn[dp[i-1]]) == ((p[i]-k-1>=0)?pn[p[i]-k-1]:0))
            dp[i] = max(dp[i], p[i]);
        //允许"上一个 P 跳过当前"的情形（i 与 i-2 组合）
        if (i>1 && ((i-2==0?-1:dp[i-2]) >= p[i]-k-1 ||
            (i-2==0?0:pn[dp[i-2]]) == ((p[i]-k-1>=0)?pn[p[i]-k-1]:0)))
            dp[i] = max(dp[i], p[i-1]+k);
        if (dp[i] < p[i]) return false;//无法覆盖到当前位置 → 失败
    }
    if (lst <= dp[d]) return true;//最后蘑菇被覆盖 → 成功
    return false;
}

int n, cnt;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i)
        if (s[i] == 'P') cnt++;
    if (cnt == 0) cout << "0 0\n";
    else if (cnt == 1) {
        int c = 0;
        for (int i = 0; i < n; ++i)
            if (s[i] == 'P') c = i;
        int l1 = 0, g1 = 0, l2 = 0, g2 = 0;
        for (int i = c-1; i >= 0; --i)
            if (s[i] == '*') g1++, l1 = c - i;
        for (int i = c+1; i < n; ++i)
            if (s[i] == '*') g2++, l2 = i - c;
        if (g1 > g2) cout << g1 << ' ' << l1 << '\n';
        else if (g1 < g2) cout << g2 << ' ' << l2 << '\n';
        else cout << g1 << ' ' << min(l1, l2) << '\n';
    } else {
        for (int i = 0; i < n; ++i)
            pn[i] = (s[i]=='*')+((i-1>=0)?pn[i-1]:0);
        for (int i = 0; i < n; ++i)
            if (s[i] == '*') lst = i;
        for (int i = 0; i < n; ++i)
            if (s[i] == 'P') p[++d] = i;
        int l = n, r = 0;
        while (l > r) {
            int mid = (l+r-1)/2;
            if (ok(mid)) l = mid; else r = mid+1;
        }
        cout << pn[n-1] << ' ' << l << '\n';
    }
    return 0;
}