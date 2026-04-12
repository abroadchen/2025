//
// Created by Psy.C on 2026/4/12.
//
/**
找到b[i]/a[i]的最小值（整数除法）
将所有b[i]减去mn*a[i]，相当于预先完成mn轮完整的操作
ans初始化为mn（已完成的轮数）
flag控制循环是否继续
遍历每个位置，检查是否有b[i] < a[i]
如果不足，用q中的资源补充
如果q不够（q <= 0），设置flag=0，结束循环
检查是否所有b[i] >= a[i]
如果不是，说明不能完成这一轮，ans--（撤销之前加的）
如果是，从每个b[i]中减去对应的a[i]
ans++，表示完成了一轮操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005, inf = 0x3f3f3f3f;
int n, q, a[N], b[N];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    int mn = inf;
    for (int i = 1; i <= n; ++i)
        mn = min(mn, b[i]/a[i]);
    for (int i = 1; i <= n; ++i) b[i] -= mn*a[i];
    int ans = mn, flag = 1;
    while (flag) {
        for (int i = 1; i <= n; ++i) {
            if (b[i] < a[i]) {
                q -= a[i] - b[i];
                if (q >= 0) b[i] = a[i];
            }
            if (q <= 0) { flag = 0; break; }
        }
        for (int i = 1; i <= n; ++i) {
            if (b[i] < a[i]) { ans--; break; }
            b[i] -= a[i];
        }
        ans++;
    }
    cout << ans << '\n';
    return 0;
}