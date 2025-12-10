//
// Created by Psy.C on 2025/12/10.
//
/*
*n: 数组元素个数
k: 最大允许代价
a[N]: 存储元素的数组
 *
*idx: 滑动窗口的左边界，初始为1
t: 当前窗口内的元素个数（不包括右端点）
sum: 当前窗口的总代价
c: 当前找到的最长序列长度，初始为1
num: 对应最长序列的元素值，初始为a[1]
 *
 *从第二个元素开始遍历，扩展滑动窗口的右边界
*d = a[i] - a[i-1]: 相邻两个排序后元素的差值
t++: 窗口内元素个数加1
sum += t * d: 更新总代价。这里t * d表示由于新元素加入导致前面t个元素都需要额外移动d的距离
 *
*当总代价超过k时，收缩滑动窗口的左边界：
sum -= a[i] - a[idx]: 减去最左边元素对总代价的贡献
idx++: 左边界右移
t--: 窗口内元素个数减1
 *
*如果当前窗口大小(t + 1)大于已记录的最大长度c：
更新最大长度c = t + 1
更新对应的元素值num = a[i]（窗口右端点的值）
 *
*时间复杂度: O(n)，每个元素最多被访问两次
空间复杂度: O(1)
 *
 *作为右端点加入窗口
 *作为左端点离开窗口
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;


int main() {
    fast;
    ll n, k, a[N]; cin>>n>>k;
    for (int i = 1; i <= n; ++i) cin>>a[i];
    sort(a + 1, a + n + 1);
    int idx = 1;
    ll t = 0, sum = 0, c = 1, num = a[1];
    for (int i = 2; i <= n; ++i) {
        const ll d = a[i] - a[i - 1]; t++;
        sum += t * d;
        while (sum > k) {
            sum -= a[i] - a[idx];
            idx++;
            t--;
        }
        if (t + 1 > c) { c = t + 1; num = a[i]; }
    }
    cout << c << ' ' << num << '\n';
    return 0;
}