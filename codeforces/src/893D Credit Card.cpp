//
// Created by Psy.C on 2026/10/9.
//
/**
n：天数。
d：上界（上限）‍——每天的值不能超过
d
d，也不能低于某个下界（通常下界是 0 或某个值）。
a[i]：每天的净变化（可为正可为负）。
s1：当前值的可能下界（lower bound）。
s2：当前值的可能上界（upper bound）。
ans：需要使用的"重置操作"次数（当 a[i]==0 时可以触发）。
核心思路：因为存在 a[i]==0 这种"可以把值设成 d 的特殊操作"，所以当前值并不是唯一确定的，而是落在一个区间 [s1, s2] 内。我们在扫的过程中维护这个区间，并在必要时动用特殊的"重置"
情况一：a[i] != 0（正常变化日）

直接把 s1、s2 都加上 a[i]（整段区间平移
a
[
i
]
a[i]）。
if (s1 > d)：如果下界已经超过上界
d
d，说明无论如何当前值都会超上限 → 无解，输出 -1。
if (s2 > d) s2 = d：上界被钳制到
d
d（值不能超上限）。
情况二：a[i] == 0（特殊日，可以使用"重置"）

这天没有实质变化（变化为 0），但可以用一次"重置操作"把值直接设成
d
d。
if (s1 < 0) s1 = 0：若当前下界为负（区间整体在下限 0 以下），把下界抬到 0（因为值不能低于 0）。
if (s2 < 0) s2 = d, ans++：若上界仍为负，说明整个可能区间都在 0 以下、已经不可能通过自然变化回到合法范围，必须用一次重置把它设成
d
d：ans++，并把上界设回
d
d
输出需要的最少重置次数 ans；若过程中下界超过
d
d，提前输出 -1 结束
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;
int n, s1, s2, ans;
ll d, a[N];
int main() {
    fast;
    cin >> n >> d;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] != 0) {
            s1 += a[i], s2 += a[i];
            if (s1 > d) { cout << -1; return 0; }
            if (s2 > d) s2 = d;
        } else {
            if (s1 < 0) s1 = 0;
            if (s2 < 0) s2 = d, ans++;
        }
    }
    cout << ans;
    return 0;
}