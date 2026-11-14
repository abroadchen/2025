//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
a[i]：第 i 个元素的原始值（可能是 c，也可能是其他）。
lst[x]：最近一次看到数字 x 的位置（用于找每个元素"上一次出现"）。
last[i]：a[i] 这个值上次出现的位置（last[i] = lst[a[i]] 赋值前先读了旧值）。
cnt[i]：前缀中 c 出现次数（cnt[i] = cnt[i-1] + (a[i]==c)）。
dp[i]：以"染到 i"为结尾的某种最大收益。
输入 n, c：c 是目标数字
last[i]：值 a[i] 上次出现位置（不重复同一值），默认 0 表示未出现过；
lst[]：辅助数组实时记录每个值最近位置；
cnt[]：c 的前缀个数
对每个非 c 元素 i：

cnt[i] - cnt[last[i]]：从 last[i] 到 i 这段，c 出现的次数（用于抵消——把这段染成 c 时，原来这些 c 的位置收益会重复，需扣除）。
dp[last[i]] - (这段内c数量)：在上一处同色位置 last[i] 的 dp 基础上，减去这段时间里的 c 计数（避免重复计算原本就算过的 c）。
取 max(0, …) 防止负数，再 +1（把位置 i 染上）。
用 ans 记录所有 dp 的最大值
最终答案 = DP 得到的最大"额外收益" ans 加上原本数组里 c 的个数 cnt[n]（因为这些 c 本来就有，染色收益是在其上额外加出来的）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 5e5+5;

int n, c, a[N], last[N], lst[N], cnt[N], dp[N], ans;
int main() {
    fast;
    cin >> n >> c;
    rep(i,n) {
        cin >> a[i];
        last[i] = lst[a[i]]; lst[a[i]] = i;//更新 a[i] 最近一次为当前
        cnt[i] = cnt[i-1] + (a[i] == c);
    }
    rep(i,n) {
        if (a[i] == c) continue;
        dp[i] = max(0, dp[last[i]]-(cnt[i]-cnt[last[i]])) + 1;
        ans = max(ans, dp[i]);
    }
    cout << ans+cnt[n];
    return 0;
}