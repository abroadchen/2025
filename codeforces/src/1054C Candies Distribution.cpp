//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
x[i]：记录第 i 个元素的：
id：原编号
rk：构造出的排名（最终会输出）
s：l[i]+r[i]
cmp：按 s 降序排（s 大者排前，即"两边更大数更多"的靠前）
读入 l[]、r[]。
对每个 i 记录 s = l[i]+r[i]，原始编号 id=i
按 s 降序排序后，从大到小赋排名：
第一个 x[1].rk = 1。
从 i=2 起：若 x[i].s != s（数值有变化）则排名 +1 并更新 s；否则并列（.s 相同则排名相同）。
效果：相同 s 并列、s 更小者排名更大——a[x[i].id] = x[i].rk，即 s 越大（倒序数越多）排名越小（这个数越大）
把每个元素的排名写回它原本编号的位置，构造出排列 a（1..n 各出现一次，无重复）
对每个 i：
统计它左边 a[j] > a[i] 的个数，从 l[i] 里减去。如果 l[i] 正好等于左边更大数的个数，减完应为 0。
统计右边 a[j] > a[i] 的个数，从 r[i] 里减去。
若任一 l[i] 或 r[i] 减完不等于 0，说明构造的排列不满足给定条件 → 输出 NO 结束。
全部通过 → 输出 YES
输出 YES，然后输出构造出的排列 a[1..n]（用 write 快写，数字间空一格，最后换行）
*/
#include <bits/stdc++.h>
#define rep(i,n) for (i=1; i<=(n); i++)
#define int long long
using namespace std;

constexpr int N = 1005;

struct node { int id, rk, s; } x[N];
bool cmp(node a, node b) { return a.s > b.s; }


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, l[N], r[N], a[N];
signed main() {
    cin >> n; int i, j;
    rep(i,n) l[i] = rd();
    rep(i,n) r[i] = rd();
    rep(i,n) x[i].s = l[i] + r[i], x[i].id = i;
    sort(x+1, x+n+1, cmp); x[1].rk = 1;
    int s = x[1].s;
    for (i = 2; i <= n; i++) x[i].s != s ? (x[i].rk = x[i-1].rk+1, s = x[i].s) : x[i].rk = x[i-1].rk;
    rep(i,n) a[x[i].id] = x[i].rk;
    rep(i,n) {
        rep(j,i-1) if (a[j] > a[i]) l[i]--;
        for (j = i+1; j <= n; j++) if (a[j] > a[i]) r[i]--;
        if (l[i] != 0 || r[i] != 0) { cout << "NO\n"; return 0; }
    }
    cout << "YES\n";
    rep(i,n) write(a[i]), putchar(' ');
    cout << '\n';
    return 0;
}