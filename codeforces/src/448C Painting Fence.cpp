//
// Created by Psy.C on 2026/2/9.
//
/**
1ll*r-l+1：直接涂色整个区间，每个位置单独处理
sum：分层处理的总代价
 */
///时间复杂度：O(n²)最坏情况，平均情况下更快 空间复杂度：O(n)（数组存储）+ O(log n)（递归栈深度）
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define inf 0x3f3f3f3f
using namespace std;

int a[N];//存储输入的高度值
ll dfs(const int l, const int r, const int h) {//左右边界l,r和当前高度h
    if (l == r) return 1;//最小操作数
    int hh = inf;
    for (int i = l; i <= r; ++i) hh = min(hh, a[i]);
    ll sum = hh - h;//当前层需要的操作数：最小值减去当前高度
    for (int i = l; i <= r; ++i) {
        if (a[i] == hh) continue;
        int j = i;
        while (a[j+1] > hh) j++;//找到连续的高于最小值的区间[i,j]
        sum += dfs(i, j, hh);//递归处理子区间[i,j]
        i = j;//跳过已处理的区间
    }
    return min(1ll*r-l+1, sum);
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cout << dfs(1, n, 0) << '\n';
    return 0;
}