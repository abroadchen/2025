//
// Created by Psy.C on 2026/9/27.
//
/**
n：每组应该分的元素个数。
k[201]：存 2n 个数的数组（开 201 是为了容纳最大情况下的 2n 个元素）
读入 n，然后读入共 2n 个整数存入 k[1]...k[2n]
把这 2n 个数从小到大排序
排好序后，前 n 个是"较小的一半"，后 n 个是"较大的一半"。
关键在于：只有当"较小一半的最大值 k[n]"严格小于"较大一半的最小值 k[n+1]"时，才能分成左右两组满足"第一组所有数 < 第二组所有数"。
k[n] < k[n+1] 成立 → 输出 YES；否则输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k[201];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= 2*n; ++i) cin >> k[i];
    sort(k+1, k+2*n+1);
    if (k[n] < k[n+1]) cout << "YES"; else cout << "NO";
    return 0;
}