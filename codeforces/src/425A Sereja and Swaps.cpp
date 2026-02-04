//
// Created by Psy.C on 2026/2/4.
//
/**
* a[N]：原数组
b[N]：副本数组（用于操作）
k：最大操作次数
n：数组长度
*p：区间外最大值的位置
q：区间内最小值的位置
 *
*枚举区间：O(n²)
每次get操作：O(k×n)
总体复杂度：O(n³×k)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 205
#define inf 0x3f3f3f3f
using namespace std;

int a[N], b[N], k, n;
int get(const int l, const int r) {//将区间外的最大值与区间内的最小值交换
    memcpy(b, a, sizeof a);
    int ans = 0;
    for (int i = l; i <= r; ++i) ans += a[i];//区间[l,r]的初始和
    for (int i = 0, p = 0, q = 0; i < k; ++i) {//最多k次操作
        int mx = -inf, mn = inf;
        for (int j = 1; j <= n; ++j) {
            if ((j < l || j > r) && b[j] > mx) {//在区间外寻找最大值
                mx = b[j]; p = j;
            } else if (j >= l && j <= r && b[j] < mn) {//在区间内寻找最小值
                mn = b[j]; q = j;
            }
        }
        const int t = mx - mn;
        if (t <= 0) break;
        ans += t;//更新结果
        swap(b[p], b[q]);//交换区间内外的元素
    }
    return ans;
}


int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = -inf;
    for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j)//枚举所有可能的区间
        ans = max(ans, get(i, j));//所有区间的最大结果
    cout << ans << '\n';
    return 0;
}