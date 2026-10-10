//
// Created by Psy.C on 2026/10/10.
//
/**
t[x]：记录"以 x 为最大元素"的次大贡献次数
vis[x]：标记 x 是否是原序列中的最大值（出现过作为全局最大）
mx：当前已见最大值
nmx：当前已见次大值
对每个元素 x：

若 x > mx：说明 x 成为新的最大值，原最大值 mx 降级为次大值 nmx。同时 vis[x] = 1 标记 x 曾作为全局最大出现过。
否则若 x > nmx（即 nmx < x ≤ mx）：x 成为新的次大值 nmx，此时 t[mx]++——表示 "当前最大值 mx 因为遇到了一个介于它和旧次大之间的元素而赚到了一次"
从 n 往下枚举所有候选 i（i 的取值涵盖所有出现过的值区间 [1..n]），用 t[i] - vis[i] 打分，取分数最大者；>= 保证并列时取编号较大的（因为从大到小扫，后面遇到更大的 i 会覆盖）。初始 ans = 1，若所有 t[i]-vis[i] 都非正，则输出 1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, t[N], vis[N];
int main() {
    fast;
    cin >> n;
    int mx = 0, nmx = 0;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x > mx) { nmx = mx; mx = x; vis[x] = 1; }
        else if (x > nmx) { nmx = x; t[mx]++; }
    }
    int ans = 1;
    for (int i = n; i >= 1; --i)
        if (t[i] - vis[i] >= t[ans] - vis[ans])
            ans = i;
    cout << ans;
    return 0;
}