//
// Created by Psy.C on 2026/2/18.
//
/**
时间复杂度：O(n²)（选择排序的时间复杂度）
空间复杂度：O(n²)（存储操作记录）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3001;
int n, a[N], res[N][2];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int mn = a[i], x = i;//最小值为当前位置的值，索引为i
        for (int j = i + 1; j < n; ++j) if (a[j] < mn) {//找到更小的元素
            mn = a[j];
            x = j;
        }
        if (x == i) continue;//最小值就在当前位置
        res[cnt][0] = i;//交换的第一个位置
        res[cnt++][1] = x;//交换的第二个位置
        swap(a[i], a[x]);
    }
    cout << cnt << '\n';//交换操作的次数
    for (int i = 0; i < cnt; ++i)
        cout << res[i][0] << ' ' << res[i][1] << '\n';
    return 0;
}