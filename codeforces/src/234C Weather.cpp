//
// Created by Psy.C on 2025/12/12.
//
/*
*a[N]：存储原始数据
l[N]：存储以每个位置为分割点时，左侧需要修改为非负数的元素个数
r[N]：存储以每个位置为分割点时，右侧需要修改为非正数的元素个数
 *
*从右向左计算r数组（后缀）：
从倒数第二个位置开始向前遍历
如果a[i+1]是非正数(≤0)，则r[i] = r[i+1] + 1（需要修改的元素增加1个）
否则r[i] = r[i+1]（保持不变）
 *
*从左向右计算l数组（前缀）：
从第二个位置开始向后遍历
如果a[i-1]是非负数(≥0)，则l[i] = l[i-1] + 1（需要修改的元素增加1个）
否则l[i] = l[i-1]（保持不变）
 *
*j初始化为r[0]，表示以位置0为分割点时右侧需要修改的元素个数
k初始化为l[n-1]，表示以位置n-1为分割点时左侧需要修改的元素个数
*如果第一个元素a[0]是非负数，则j加1（因为要把它放在左侧，而左侧应全为非负数，所以不需要修改）
如果最后一个元素a[n-1]是非正数，则k加1（因为要把它放在右侧，而右侧应全为非正数，所以不需要修改）
 *
 *初始化m为j和k中的较小值，作为当前最小修改次数
 *
*遍历中间位置作为分割点（从位置1到n-2）：
如果当前元素a[i]不等于0，则比较m与(r[i] + l[i])的大小，取较小值
如果当前元素a[i]等于0，则比较m与(r[i] + 1 + l[i])的大小，取较小值
这里考虑了当前元素归属的问题：如果a[i]是0，它可以属于左侧或右侧，不影响条件，但在某些情况下可能需要额外考虑
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, i; cin>>n;
    int a[N], l[N], r[N];
    for (i = 0; i < n; ++i) cin>>a[i];
    r[n - 1] = 0;//以最后一个元素为分割点时
    for (i = n - 2; i >= 0; --i) {
        if (a[i + 1] <= 0) r[i] = r[i+1] + 1;
        else r[i] = r[i+1];
    }
    l[0] = 0;//以第一个位置为分割点时
    for (i = 1; i < n; ++i) {
        if (a[i - 1] >= 0) l[i] = l[i - 1] + 1;
        else l[i] = l[i - 1];
    }
    int j = r[0], k = l[n-1];
    if (a[0] >= 0) j++;
    if (a[n-1] <= 0) k++;
    int m = min(j, k);
    for (i = 1; i < n - 1; ++i) {
        if (a[i] != 0) m = min(m, r[i] + l[i]);
        else m = min(m, r[i] + 1 + l[i]);
    }
    cout << m << '\n';
    return 0;
}