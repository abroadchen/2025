//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
n：数组元素个数
m：可分配的"总增量"预算
a[]：数组
mx：数组当前最大值
ans：二分求出的某个答案
读入 n、m 和数组，并记录当前最大值 mx
二分下界 l = mx（新最大值不可能小于原最大值），上界 r = mx + m。
对每个 mid：
计算 sum = Σ(mid - a[i])：如果要把所有元素都抬到 mid，需要的总增量。
若 sum >= m：说明用 m 的预算有可能把所有元素抬到 mid，则收窄上界（r = mid-1）并记录 ans = mid。
否则（sum < m）：预算不够把所有元素抬到 mid，只能把下界上调（l = mid+1）
输出两个数：
ans：通过二分找到的能统一抬到的最高高度（新最大值的最小可行值）‍。
mx + m：原最大值 + 所有 m 预算全加在原最大值上所得的"可能达到的最大值"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105;

int n, m, a[N], mx, ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    int l = mx, r = mx + m;
    while (l <= r) {
        int mid = (l + r) >> 1, sum = 0;
        for (int i = 1; i <= n; i++) sum += mid - a[i];
        if (sum >= m) ans = mid, r = mid - 1; else l = mid + 1;
    }
    cout << ans << ' ' << mx + m << '\n';
    return 0;
}