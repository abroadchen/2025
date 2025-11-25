//
// Created by Psy.C on 2025/11/25.
//
/*
*n: 矩阵的大小（n×n）
cnt: 满足条件的元素计数器
a[N][N]: 存储输入矩阵
b[N]: 存储每行的和（初始化为0）
c[N]: 存储每列的和（初始化为0）
 *
*外层循环固定行索引 i
内层循环遍历所有列索引 j
 *
*时间复杂度：O(n²)
空间复杂度：O(n²)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

constexpr int N = 30;
int n, cnt, a[N][N], b[N]={}, c[N]={};

int main() {
    fast;
    cin >> n;
    rep(i,n) rep(j,n) { cin >> a[i][j]; b[i] += a[i][j]; }
    rep(j,n) rep(i,n) c[j] += a[i][j];
    rep(i,n) rep(j,n) if (b[i] < c[j]) cnt++;
    cout << cnt << '\n';
    return 0;
}