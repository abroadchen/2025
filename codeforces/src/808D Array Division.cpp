//
// Created by Psy.C on 2026/9/20.
//
/**
pre[i] = 前 i 个元素的和（前缀和）。
pre[n] = 整个数组总和
若总和是奇数，不可能分成两个相等的整数和 → 直接 NO。
否则目标是每半和 = sum = pre[n]/2
情况 A：check(sum - a[i], 1, i-1)

在前缀和 pre[1..i-1]（即 i 左边的前缀和）中找是否存在 sum - a[i]。
含义：表示"把元素 a[i] 从右边挪到左边"。若某左侧位置 j 满足 pre[j] = sum - a[i]，意味着把 a[i] 移过去后，左段和右段能达到平分。
数学：原左段和为 sum - a[i]，加上挪来的 a[i] 变成 sum（右边则相应减 a[i] 也变 sum）。
情况 B：check(sum + a[i], i+1, n)

在前缀和 pre[i+1..n]（i 右边的前缀和）中找是否存在 sum + a[i]。
含义：表示"把元素 a[i] 从左边挪到右边"。若某右侧位置 j 满足 pre[j] = sum + a[i]，即右段原本和为 sum + a[i]，挪走 a[i] 后变成 sum（左边加上 a[i] 也变 sum）。
check 就是在这段前缀和区间里二分查找目标值是否出现（因为 pre 单调递增，a[i] 全为正，可二分）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

ll pre[N];
bool check(ll t, int l, int r) {
    while (l <= r) {
        int mid = (l+r)>>1;
        if (pre[mid] == t) return true;
        if (pre[mid] > t) r = mid-1;
        else if (pre[mid] < t) l = mid+1;
    }
    return false;
}

int a[N];
int main() {
    fast;
    int n;
    while (cin >> n) {
        pre[0] = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pre[i] = pre[i-1]+a[i];
        }
        if (pre[n]%2) { cout << "NO\n"; continue; }
        ll sum = pre[n]/2;
        int flag = 0;
        for (int i = 1; i <= n; ++i)
            if (check(sum-a[i], 1, i-1) || check(sum+a[i], i+1, n))
                flag = 1;
        if (flag == 1) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}