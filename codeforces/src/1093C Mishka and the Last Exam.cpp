//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
a[N]：要构造的结果序列。
b[N]：输入的对称和
读入 n，b[1..n/2] 对称和。
a[n+1] = 2^62（很大的哨兵，作为循环里"右边邻居"的初始上限），这个哨兵保证第一步比较不会误触发
为了让序列非递减，左端 a[i] 至少要 ≥ a[i-1]，所以先令 a[i]=a[i-1]（取能取的最小值，以给右端留出更大空间）。
再由对称和定义算出右端 a[n-i+1] = b[i] - a[i]
右端 a[n-i+1] 必须不大于它右边的邻居 a[n-i+2]（因为序列非递减，越靠右值越大，所以它是右端里面靠左的那个）。
若算出来的右端比它右边邻居还大 → 违反单调。此时强制右端 = 右边邻居，再反推左端 a[i] = b[i] - a[n-i+1]
输出构造出的完整序列
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;


ll a[N], b[N];
int main() {
    fast;
    int n; cin >> n;
    rep(i,n/2) cin >> b[i];
    a[n+1] = 1ll<<62;
    rep(i,n/2) {
        a[i] = a[i-1]; a[n-i+1] = b[i] - a[i];
        if (a[n-i+1] > a[n-i+2]) {
            a[n-i+1] = a[n-i+2];
            a[i] = b[i] - a[n-i+1];
        }
    }
    rep(i,n) cout << a[i] << ' ';
    return 0;
}