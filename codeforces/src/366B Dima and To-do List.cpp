//
// Created by Psy.C on 2026/1/20.
//
/**
 * n（输入元素个数）和k（分组数）
 *
 *设置前k个元素的id为1到k（1-indexed）
 *i%k：将第i个元素分配到组i%k
 *
*输入处理：O(n)
排序：O(k log k)
总体：O(n + k log k)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

struct node { int val, id; } a[N];

int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i < k; ++i) a[i].id = i + 1;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        a[i%k].val += x;//将x累加到对应组的val中
    }
    //对前k个元素进行排序
    sort(a, a + k, [](const node a, const node b) {
        if (a.val == b.val) return a.id < b.id;
        return a.val < b.val;
    });
    cout << a[0].id << '\n';
    return 0;
}