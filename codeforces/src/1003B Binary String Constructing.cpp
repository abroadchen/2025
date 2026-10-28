//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
ans[i] = i&1：下标偶数位放 0、奇数位放 1（即以 0 开头的交替串：0 1 0 1 ...）。
每放一个字符就把对应剩余量减 1（a-- 或 b--）。
交替阶段让 0 开头的优势端成为"开头"：因为 0 的数量多，让 0 占据更多交替位（偶数位比奇数位多一位），消耗更多 0。
cnt[0] += a; cnt[1] += b;：把交替后剩余的 0 全补到 0 的计数后，剩余的 1 补到 1 的计数后——即末尾同类字符连续追加，不增加变化次数。
因为 a > b，0 多、1 少，所以交替串以 0 开头能尽量多消耗 0、且保证 1 不会被交替阶段消耗完导致无法补足。这是贪心的关键
ans[i] = -i&1：偶数位放 1、奇数位放 0（即以 1 开头的交替串：1 0 1 0 ...）。
因为 b >= a（1 多），让交替串以 1 开头，多消耗 1。
注意 ！这里补段是反过来的：cnt[0] += b; cnt[1] += a——把剩余的 1 补到 cnt[0]（即 0 这一坨）后面，把剩余的 0 补到 cnt[1]（1 这一坨）后面
外层 i 从 0..x 依次输出交替串的每一位，内层把该位字符连续输出 cnt[i]-1 次。
因为交替阶段每位置初始 cnt=1（各打印 1 次），加上末尾补的同类 cnt[0]、cnt[1] 都大于 1（剩余字符追加），于是这些同字符连续打印、不产生额外变化
最终字符串 = (交替串 0..x) 但每一类的最后几段被"加长"，使变化次数仍恰好为 x
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i <= n; i++)
using namespace std;

constexpr int N = 201;

int a, b, x, ans[N], cnt[N];
int main() {
    fast;
    cin >> a >> b >> x;
    if (a > b) {
        rep(i,x) {
            ans[i] = i&1, cnt[i] = 1;
            if (ans[i]) b--; else a--;
        }
        cnt[0] += a; cnt[1] += b;
    } else {
        rep(i,x) {
            ans[i] = ~i&1, cnt[i] = 1;
            if (ans[i]) b--; else a--;
        }
        cnt[0] += b; cnt[1] += a;
    }
    rep(i,x) rep(j,cnt[i]-1) cout << ans[i];
    return 0;
}