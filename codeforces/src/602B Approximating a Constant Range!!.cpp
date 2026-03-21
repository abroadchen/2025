//
// Created by Psy.C on 2026/3/21.
//
/**
mp: 有序映射，维护当前窗口中各数值的出现次数
初始化答案为2（至少两个元素）
设置滑动窗口 [l, r)，初始为 [0, 2)
将前两个元素加入映射
p指向最小值，e指向最大值
如果新元素与当前窗口的最值差都不超过1
否则收缩窗口左边界
如果计数为0则删除
更新最大窗口长度

时间复杂度
每个元素最多进入和离开窗口各一次
map操作：O(log n)
总体：O(n log n)
空间复杂度
O(n)：用于存储map和数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
map<int, int> mp;
int main() {
    fast;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    int ans = 2, l = 0, r = 2;
    mp[v[0]]++; mp[v[1]]++;
    while (r < n) {
        auto p = mp.begin(), e = --mp.end();
        if (abs(p->first - v[r]) <= 1 && abs(e->first - v[r]) <= 1) {
            mp[v[r]]++;
            r++;
        } else {
            mp[v[l]]--;
            if (mp[v[l]] == 0) mp.erase(v[l]);
            l++;
        }
        ans = max(ans, r-l);
    }
    cout << ans << '\n';
    return 0;
}