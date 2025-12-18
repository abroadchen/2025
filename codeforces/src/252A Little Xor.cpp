//
// Created by Psy.C on 2025/12/17.
//
/*
*x[0] = 0（空数组的异或和）
x[i] = x[i-1] ^ a[i]
从索引i到j的子数组异或和 = x[j] ^ x[i-1]
 *
*外层循环i从0到n-1（子数组起始位置的前一个位置）
内层循环j从i+1到n（子数组结束位置）
计算从位置i+1到j的子数组异或和：x[j] ^ x[i]
更新最大值
 *
*时间复杂度：O(n²)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 101
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int x[N] = {};//前缀异或数组 a[1] ^ a[2] ^ ... ^ a[i]
    for (int i = 1, a; i <= n; ++i) {
        cin>>a;
        x[i] = x[i-1] ^ a;
    }
    int mn = 0;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j <= n; ++j) {
        const int t = x[i] ^ x[j];
        if (t > mn) mn = t;
    }
    cout<<mn<<'\n';
    return 0;
}