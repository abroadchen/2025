//
// Created by Psy.C on 2026/2/9.
//
/**
n: 数组长度
a[N]: 输入数组（long long类型）
f[N]: 从左往右的递增序列长度
f2[N]: 从右往左的递减序列长度

f[i]: 以位置i结尾的从左往右的最长递增序列长度
从左往右扫描，如果a[i] > a[i-1]，则延续之前的递增序列
f2[i]: 以位置i开始的从右往左的最长递减序列长度
从右往左扫描，如果a[i] < a[i+1]，则延续之后的递减序列

找到左边递增序列的最大长度+1（跳过一个元素）
找到右边递减序列的最大长度+1（跳过一个元素）

检查能否删除中间元素，将左右两段连接起来
a[i+1] - a[i-1] >= 2: 确保跳过a[i]后，a[i-1]和a[i+1]仍然可以构成递增序列
f2[i+1] + f[i-1] + 1: 左边递增序列 + 右边递减序列 + 当前元素

f[i] + 1: 删除当前元素，保留左边的递增序列
f2[i+1] + 1: 删除当前元素，保留右边的递减序列
f2[i+1] + f[i-1] + 1: 删除中间元素，连接左右两段（要求a[i-1]和a[i+1]能形成递增）


 */

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

int n, f[N], f2[N];
ll a[N];

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (n == 1) cout << "1\n";
    else if (n == 2) cout << "2\n";
    else {
        f[1] = 1;
        for (int i = 2; i <= n; ++i) {
            f[i] = 1;
            if (a[i] > a[i-1]) f[i] = f[i-1] + 1;
        }
        f2[n] = 1;
        for (int i = n - 1; i >= 1; --i) {
            f2[i] = 1;
            if (a[i] < a[i+1]) f2[i] = f2[i+1] + 1;
        }
        int res = 0;
        for (int i = 1; i <= n - 1; ++i)
            if (a[i] >= a[i+1]) res = max(res, f[i] + 1);
        for (int i = n - 1; i >= 1; --i)
            if (a[i] >= a[i+1]) res = max(res, f2[i+1] + 1);
        for (int i = 2; i <= n - 1; ++i)
            if (a[i+1] - a[i-1] >= 2) res = max(res, f2[i+1] + f[i-1] + 1);
        cout << res << '\n';
    }
    return 0;
}