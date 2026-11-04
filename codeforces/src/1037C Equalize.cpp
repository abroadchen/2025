//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
a、b 是两个长度为 n 的 01 字符串。
c[i+1] 存的是 a[i] 与 b[i] 的异或结果（1 表示两字符不同，0 表示相同）。
c[n+1]=0 在末尾补一个哨兵。
也就是说，c 把 a、b 按位比较的差异标记出来，1 表示"不一样"
这是对 c 数组做分段扫描：每当遇到 c[i]==0，就统计它前面连续的一段 1 的长度 cnt。即把连续的"差异位"成段处理。

然后按这段连续 1 的长度分情况：
① cnt == 1（只有 1 个差异位）
→ 需要 1 次操作。
② cnt == 2（连续 2 个差异位）
→ 根据 b 中对应位置（这两段差异前面两位 b[i-3] 与 b[i-2]）是否相等，决定加 1 还是加 2
③ cnt == 0

→ continue，无操作。

④ cnt ≥ 3（较长连续段）
→ 逐位扫描这段，根据 b 相邻位是否相等累加操作次数，并用 vis 记录已处理位置。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+5;

int n, c[N];
string a, b;
bool vis[N];
int main() {
    fast;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        bool f1 = false, f2 = false;
        if (a[i] == '1') f1 = true;
        if (b[i] == '1') f2 = true;
        c[i+1] = f1^f2;
    }
    c[n+1] = 0;
    int ans = 0;
    for (int i = 1; i <= n+1; i++) if (c[i] == 0) {
        if (i == 1) continue;
        int cnt = 0;
        for (int j = i-1; j >= 0; j--) if (c[j] == 1) cnt++; else break;
        if (cnt == 1) { ans++; continue; }
        if (cnt == 2) {
            if (b[i-3] == b[i-2]) ans += 2; else ans++;
            continue;
        }
        if (cnt == 0) continue;
        for (int j = i-cnt; j < i-1; j++) {
            vis[j-1] = true;
            if (b[j-1] != b[j]) { vis[j] = true; ans++; j++; }
            else { vis[j-1] = true; ans++; }
        }
        if (!vis[i-2]) ans++;
    }
    cout << ans << '\n';
    return 0;
}