//
// Created by Psy.C on 2026/1/30.
//
/**
* l[N]：存储每个区间的左端点
r[N]：存储每个区间的右端点
vis[N]：访问标记数组，用于标记数字是否在交集中
tot：计数器，统计最终结果
 *
*将第一个区间[l[0]+1, r[0]]内的所有整数标记为1
注意这里是开闭区间(l[0], r[0]]，所以从l[0]+1开始
 *
*遍历其余(n-1)个区间
对于每个区间[l[i]+1, r[i]]内的所有整数，将其标记为0
核心思想：只有在所有区间都存在的数字才会保持标记为1
 *
*统计在第一个区间范围内仍然标记为1的数字个数
这些数字就是所有区间共同覆盖的整数
 *
 *时间复杂度：O(n × R)，其中R是区间范围的大小
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int l[N], r[N], vis[N], tot = 0;
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    for (int i = l[0] + 1; i <= r[0]; ++i) vis[i] = 1;
    for (int i = 1; i < n; ++i)//对于其他每个区间，将不在该区间内的数字的标记清除
        for (int j = l[i] + 1; j <= r[i]; ++j) vis[j] = 0;
    for (int i = l[0] + 1; i <= r[0]; ++i) if (vis[i]) tot++;
    cout << tot << '\n';
    return 0;
}