//
// Created by Psy.C on 2026/10/6.
//
/**
读入 n 和三条边权 a,b,c。
n--：把"要走的总步数"减 1（后面每轮 n-- 即走一步）。
若 n == 0（即原来 n=1），不需要走路，输出 0 直接结束
状态 p 表示当前位置，可取 1、2、3。
从状态 1 出发（p=1）。
每走一步：
状态 1：可走到状态 3（费用 a）或状态 2（费用 b）。选较小的：a<b 走 3 花 a，否则走 2 花 b。
状态 2：可走到状态 1（费用 b）或状态 3（费用 c）。选较小的：b<c 走 1 花 b，否则走 3 花 c。
状态 3：可走到状态 2（费用 c）或状态 1（费用 a）。选较小的：c<a 走 2 花 c，否则走 1 花 a。
每步把所选费用累加到 ans。
走完 n 步后输出总费用 ans

可以把状态画成一个无向环：三个状态 1–2–3–1 首尾相连：

边 (1,2)：费用 b
边 (2,3)：费用 c
边 (3,1)：费用 a
每一步从当前状态走一条边到相邻状态，选费用较小的那条。这是一个三步吃一条边、状态在两两相邻间往复的过程
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, a, b, c; cin >> n >> a >> b >> c;
    int ans = 0; n--;
    if (n == 0) { cout << 0; return 0; }
    int p = 1;
    while (n > 0) {
        n--;
        if (p == 1) {
            if (a < b) { p = 3; ans += a; }
            else { p = 2; ans += b; }
        } else if (p == 2) {
            if (b < c) { p = 1; ans += b; }
            else { p = 3; ans += c; }
        } else if (p == 3) {
            if (c < a) { p = 2; ans += c; }
            else { p = 1; ans += a; }
        }
    }
    cout << ans;
    return 0;
}