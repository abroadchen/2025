//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 数组元素个数
k: 限制条件参数
a[N]: 大小为N的数组，用于存储输入数据
r: 右指针，初始化为1
s1: 结果计数器，初始化为0
 *mp，用于记录每个数字出现的次数
 *外层循环，l作为左指针从1遍历到n
 *内层while循环，右指针r从当前位置向右移动
 *如果当前元素a[r]在map中的计数加1后达到或超过k，则跳出循环
 *将a[r]加入map计数中，并将r向右移动一位
 *累加有效子数组的数量：从位置r到n的所有子数组都满足条件
 *将左指针对应的元素从map计数中减1
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 400005
using namespace std;

int n, k, a[N], r = 1, s1 = 0;
map<int, int> mp;

signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int l = 1; l <= n; ++l) {
        while (r <= n) {
            if (mp[a[r]] + 1 >= k) break;
            mp[a[r++]]++;
        }
        s1 += n - r + 1;
        mp[a[l]]--;
    }
    cout << s1 << '\n';
    return 0;
}