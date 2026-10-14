//
// Created by Psy.C on 2026/10/14.
//
/**
ans 是"当前要分配的编号/日期"，从 1 开始。它记录下一个希望分配给新区间的值
循环读入每个区间 [l, r]
若当前待分配的 ans 小于区间左端点 l，说明这个值太早、不在区间内，就把 ans 提升到 l（跳到区间起点），让它能落在该区间里。
例如当前 ans=2，而区间是 [5, 9]，则把 ans 拉到 5。
若提升后的 ans 仍然大于区间右端点 r，说明区间无法容纳该编号，输出 0（表示这个区间分配失败）。
但特判 i != 1：第一个区间（i==1）即使 r < ans 也不输出 0，而进入 else。原因：初始化 ans=1，第一个区间的合法下界本就是 1，若第一个区间 r<1 即 r<=0 区间完全无效，此时仍会走 else 输出 ans++（输出 1，ans 变 2）；这属于边界处理上的"放行"，多数题目不会出现 r<1 的非法区间，故此特判通常无实际影响
若区间能容纳 ans，就输出 ans 并把 ans 自增 1（为下一个区间准备更大的编号）。
若区间不能容纳且不是第一个区间，则不递增 ans（ans 保持不变），继续给后面的区间用
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int t, n;
int main() {
    fast;
    cin >> t;
    while (t--) {
        cin >> n;
        int ans = 1;
        for (int i = 1, l, r; i <= n; ++i) {
            cin >> l >> r;
            if (ans < l) ans = l;
            if (r < ans && i != 1) cout << 0 << ' ';
            else cout << ans++ << ' ';
        }
        cout << '\n';
    }
    return 0;
}