//
// Created by Psy.C on 2026/9/23.
//
/**
sort 把目标按从小到大排（贪心：先处理小目标，减少翻倍次数）。
对每个 a[i]：
while (a[i] > 2*k)：只要当前能量 k 小于 a[i]/2（即翻倍一次也仍不足以……确切说 a[i] > 2k），就翻倍一次并计数 s++。循环保证退出时 a[i] <= 2k。
k = ckmax(a[i], k)：处理完该目标后，能量与 a[i] 取较大者（吸收目标，若 a[i] > k 就以 a[i] 为新能量）。
输出总翻倍次数 s
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int ckmax(int x, int y) { return x > y ? x : y; }

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1005;
int a[N];
signed main() {
    fast;
    int n = read(), k = read(), s = 0;
    for (int i = 1; i <= n; ++i) a[i] = read();
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        while (a[i] > 2*k) s++, k<<=1;//能量不足则翻倍直到 a[i] <= 2k
        k = ckmax(a[i], k);//吸收该目标，能量取 max(a[i], k)
    }
    cout << s << '\n';
    return 0;
}