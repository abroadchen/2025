//
// Created by Psy.C on 2025/12/12.
//
/*
 *
*b[N]数组用于统计连续相同元素的个数 简化后续比较逻辑，避免边界检查
k是当前组的索引
mx存储最大连续相同元素个数
遍历数组，比较当前元素与下一个元素：
如果相同(h和m都相等)，则当前组计数b[k]加1
如果不同，则移动到下一组(k增加1)
 *
*遍历计数数组b找到最大值
t存储当前组的计数
更新最大值mx
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    struct node { int h, m; } a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i].h >> a[i].m;
    if (n == 0) { cout << 0 << '\n'; return 0; }
    a[n + 1].h = -1; a[n + 1].m = -1;//在数组末尾添加一个特殊节点(-1, -1)
    int b[N], k = 1, mx = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].h == a[i+1].h && a[i].m == a[i+1].m) b[k]++;
        else k++;
    }
    for (int i = 1, t; i < k; ++i) {
        t = b[i];
        if (mx < t) mx = t;
    }
    cout << mx + 1 << '\n';
    return 0;
}