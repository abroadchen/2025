//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
cur 记录当前段的数字值（1 或 0）。
c1：当前若站在全 1 段，记录其累积长度；c2 同理记录全 0 段。
当数字变化时，说明完成了一对相邻的 1 段和 0 段，此时用 min(c1,c2) 更新答案，并切换到新段
处理末尾段后再做最后一次比较。
最终输出 ans × 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;
int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int cur = a[1], c1 = 0, c2 = 0;
    if (cur == 1) c1 = 1; else c2 = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] != cur) {
            ans = max(ans, min(c1,c2));//记录当前相邻两段中较小者
            if (cur == 1) c2 = 1; else c1 = 1;//切换段，新段长=1
            cur = a[i];
        } else { if (cur == 1) c1++; else c2++; }//同段续增
    }
    ans = max(ans, min(c1,c2));
    cout << ans*2 << '\n';
    return 0;
}