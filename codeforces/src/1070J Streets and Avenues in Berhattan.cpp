//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
先把答案初始化为 k*k（一个上界，后面不断取 min）
f[x]（布尔）表示：除去字母 i 之外的其它字母，能否凑出总个数恰为 x。
外层 j 遍历每个非 i 的字母，cnt[j] 是该字母个数（当作物品重量），f[l] |= f[l - cnt[j]]，倒序更新。
→ f 得到："其它字母能凑出的全部可能总数集合"
对每个 j（其它字母凑出 j 个，且能凑出），用 n 和 m 反推：

a = max(0, n - j)：n 还缺多少个；
b = max(0, m - (k - cnt[i] - j))：m 还缺多少个（k-cnt[i]-j 是其它字母凑 j 后剩下的其它字母个数）；
若 a + b <= cnt[i]，说明能靠字母 i 补足缺口（a 和 b 都是由字母 i 提供的），则候选解 a*b。
求所有可行候选里 a*b 的最小值

l-cnt[j] 的含义
它表示在倒序枚举容量 l 时，减去"当前这组物品（字母 j）的数量 cnt[j]"，即『不取这组时的剩余可达成量』。

若 f[l-cnt[j]] 为真（不用字母 j 就能凑出 l-cnt[j] 个），那么加上字母 j 这组 cnt[j] 个，就能凑出 l 个；
于是把 f[l] 标记为真，表示"总数 l 是可达的"。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int n, m, k, cnt[26], f[N];
string s;
void solve() {
    cin >> n >> m >> k >> s; s = " " + s;
    for (int i = 0; i <= 25; ++i) cnt[i] = 0;
    for (int i = 1; i <= k; ++i) cnt[s[i]-'A']++;
    ll ans = 1ll*k*k;
    for (int i = 0; i <= 25; ++i) {
        for (int j = 0; j <= k; ++j) f[j] = 0;
        f[0] = 1;
        for (int j = 0; j <= 25; ++j) if (i != j)
            for (int l = k; l >= cnt[j]; --l) f[l] |= f[l-cnt[j]];
        for (int j = max(0,n-cnt[i]); j <= k; ++j) if (f[j]) {
            int a = max(0,n-j), b = max(0,m-(k-cnt[i]-j));
            if (a+b <= cnt[i]) ans = min(ans, 1ll*a*b);
        }
    }
    cout << ans << '\n';
}

int T;
int main() {
    fast;
    cin >> T;
    while (T--) solve();
    return 0;
}