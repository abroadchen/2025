//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
读入后原地累加，得到前缀和数组：a[i] = a[1]+…+a[i]。
之后 a[l] 直接表示前缀 [1..l] 的和；a[n]-a[r-1] 表示后缀 [r..n] 的和
l 从 1 → n，r 从 n → …，两指针相向移动。
外层 for(l=1; l<=r; l++)：每次固定一个 l（即固定前缀和 a[l]）。
内层 for(; 后缀[r] < 前缀[l] && r>=l; r--)：
只要后缀和还小于前缀和，就把 r 往左拉大，使后缀和变大（r 变小 → 后缀区间变大 → 和变大）。
r>=l 限制不能越过前缀。
内层退出的实质：不断让后缀和 追上 / 逼近 当前前缀和
若此时 r>=l（区间不冲突）且后缀和恰好等于前缀和，则更新 ans = a[l]。
因为 l 是递增的，a[l] 严格递增（元素为正时），所以最后保留下来的 ans 就是最大的、可取得的相等前缀和后缀和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e7+1;
int n;
ll a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int l = 1, r = n; l <= r; l++) {
        for (; a[n]-a[r] < a[l] && r >= l; r--) {}
        if (r >= l && a[n]-a[r] == a[l]) ans = a[l];
    }
    cout << ans;
    return 0;
}