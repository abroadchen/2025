//
// Created by Psy.C on 2026/2/16.
//
/**
时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 100005;
int n, k, num[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) num[i] = i;// [1, 2, 3, ..., n]
    for (int i = k, t = 0; i > 0; --i) {//处理前k个位置
        if ((k-i)&1) {//i的位置相对k偏移奇数位
            num[i] = k - t;//递减序列
            t++;
        } else {
            num[i] = t + 1;//递增序列
        }
    }
    for (int i = 1; i <= n; ++i) cout << num[i] << ' ';
    return 0;
}