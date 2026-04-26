//
// Created by Psy.C on 2026/4/25.
//
/**
n：数组长度
s：特殊位置索引
a[N]：主数组
cnt[N]：计数数组，统计每个数值出现次数

如果特殊位置s的值不为0：
操作次数ans加1
减少原值的计数
将该位置设为0，并更新0的计数
对数组排序
op：当前最大的值+1
y：除特殊位置外的0的个数
寻找可用的最大值：while(cnt[op] + y == 0) op-- 找到一个还有剩余的值
终止条件：当i > op && y == 0时结束循环
处理缺失的数字：
如果cnt[i] == 0，说明缺少数字i
如果还有0可用(y != 0)，用0替换为i
否则，用最大的可用数替换为i

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+7;
int n, s, a[N], cnt[N];
int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int ans = 0;
    if (a[s] != 0) {
        ans++; cnt[a[s]]--;
        a[s] = 0; cnt[0]++;
    }
    sort(a + 1, a + n + 1);
    int op = a[n] + 1, y = cnt[0] - 1;
    for (int i = 1; ; ++i) {
        while (cnt[op] + y == 0) op--;
        if (i > op && y == 0) break;
        if (cnt[i] == 0) {
            if (y != 0) {
                ans++; y--; cnt[i]++;
            } else {
                cnt[op]--; cnt[i]++; ans++;
            }
        }
    }
    cout << ans;
    return 0;
}