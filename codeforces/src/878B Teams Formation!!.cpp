//
// Created by Psy.C on 2026/10/6.
//
/**
n 个元素，k 个相同消除，数组重复 m 次
用栈 p 做相邻压缩消除：
若栈顶元素值与当前不同，压入 {a[i], 1}。
若相同，栈顶计数 +1 并对 k 取模（(cnt+1)%k）。
若取模后为 0（累积满 k 个），则整组弹出（--top）。
这一步把单次数组压成"消不动"的栈 p[1..top]，每个栈帧的值互不相同（p[i].first 都不相等，因为同值会合并）
r1 = 单次数组压缩后的剩余元素总数
因为数组要重复 m 次，前一次结尾（栈顶 p[r]）与下一次开头（p[l]）会相连。若首尾值相同且计数和能被 k 整除，则这两段合并后能整体消除掉，继续向内收缩。
r2 = 在重复过程中"跨段被额外消掉"的元素数（每一对首尾相接消掉 p[l]+p[r] 个，累加）
情况 A：l == r（首尾收缩到同一个中间元素）‍

此时只剩一个"中轴"元素 p[l]，m 次重复中它会出现 m 次，每段周围还会被两侧消灭。
p[l].second * m % k：中轴元素在整串里出现的总次数 p[l].second * m 对 k 取模。若为 0，说明中轴也能被全部消除（消到 0），此时整个串被消光，ans -= r2（因为 r2 已计过，需要修正）。
m*r1：m 段总长（单段 r1）。
r2*(m-1)：连接处消除的影响（每处消 r2）。
p[l].second*m/k*k：中轴总次数里被整 k 消除掉的部分。
情况 B：l < r（中间还剩一个内部块）‍

若收缩后首尾 p[l] 与 p[r] 值相同（但计数和不能被 k 整除，因为若能整除会在 while 里继续消），则它们连接时消掉 (p[l]+p[r])/k*k 个。
ans = m*r1 - r2*(m-1)：总长减去 m-1 处连接消除的 r2。
6. 输出 ans，即 m 次重复后消不动的元素总数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+7;
int n, m, a[N], top, r1, r2, l, r, k, ans;
ii p[N];
signed main() {
    fast;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (!top || p[top].first != a[i]) p[++top] = {a[i], 1};
        else p[top].second = (p[top].second+1)%k;
        if (p[top].second == 0) --top;
    }
    for (int i = 1; i <= top; ++i) r1 += p[i].second;
    l = 1, r = top;
    while (l < r && p[l].first == p[r].first && (p[l].second+p[r].second)%k == 0)
        r2 += p[l].second+p[r].second, l++, r--;
    if (l == r) {
        if (p[l].second*m%k == 0) ans -= r2;
        ans += m*r1-r2*(m-1)-(p[l].second*m/k*k);
    } else {
        if (p[l].first == p[r].first) r2 += (p[l].second+p[r].second)/k*k;
        ans = m*r1-r2*(m-1);
    }
    cout << ans << '\n';
    return 0;
}