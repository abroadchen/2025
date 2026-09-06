//
// Created by Psy.C on 2026/9/5.
//
/**
a / b / c: 三种不同类型任务的最大选取数量上限。
m: 总任务数量
am[]: 存储所有 U 类型任务的价值。
bm[]: 存储所有 P 类型任务的价值。
ucnt / pcnt: 分别记录 U 类和 P 类任务的实际数量。
s[]: 临时读取任务类型字符数组

遍历 m 次，每次读取：
x: 当前任务的价值（或权重）。
s: 一个字符串，表示任务类型（'U' 或其他）。
根据首字符判断类型：
如果是 'U'，则将价值存入 am[] 并递增 ucnt。
否则（默认视为 'P'），存入 bm[] 并递增 pcnt

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e6+50;

int a, b, c, m, am[N], bm[N], ucnt, pcnt;
char s[N];
void init() {
    cin >> a >> b >> c >> m;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x >> s;
        if (s[0] == 'U') am[++ucnt] = x;
        else bm[++pcnt] = x;
    }
}

ll ans, mcnt;
int p[N];
//先选取高价值的前 a/b 项，再填补剩余空间
void solve() {
    sort(am+1, am+ucnt+1);
    sort(bm+1, bm+pcnt+1);
    for (int i = 1; i <= a && am[i] > 0; ++i)
        ans += am[i], mcnt++;
    for (int i = 1; i <= b && bm[i] > 0; ++i)
        ans += bm[i], mcnt++;
    int cnt = 0;
    for (int i = a+1; i <= ucnt; ++i) p[++cnt] = am[i];
    for (int i = b+1; i <= pcnt; ++i) p[++cnt] = bm[i];
    sort(p+1, p+cnt+1);
    for (int i = 1; i <= c && p[i] > 0; ++i)
        ans += p[i], mcnt++;
}
void out() {
    cout << mcnt << ' ' << ans << '\n';
}

int main() {
    fast;
    init(); solve(); out();
    return 0;
}