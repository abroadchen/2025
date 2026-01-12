//
// Created by Psy.C on 2026/1/12.
//
/**
* cnt[5] == 0 && cnt[7] == 0：数字5和7不能出现
cnt[2] >= cnt[4]：数字2的数量不少于数字4的数量
cnt[1] == cnt[4] + cnt[6]：数字1的数量等于4和6的数量之和
cnt[2] + cnt[3] == cnt[4] + cnt[6]：2和3的数量之和等于4和6的数量之和
 *
*cnt[4] 个 "1 2 4" 组：使用 cnt[4] 个1、2、4
剩余的2与1、6组成 "1 2 6" 组
所有3与1、6组成 "1 3 6" 组
 *
*满足条件时：

(1,2,4) 三元组数量：cnt[4]
(1,2,6) 三元组数量：cnt[2] - cnt[4]
(1,3,6) 三元组数量：cnt[3]
验证：

1的总数：cnt[4] + (cnt[2]-cnt[4]) + cnt[3] = cnt[2] + cnt[3] = cnt[4] + cnt[6] ✓
6的总数：(cnt[2]-cnt[4]) + cnt[3] = cnt[2] + cnt[3] - cnt[4] = (cnt[4] + cnt[6]) - cnt[4] = cnt[6] ✓
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, cnt[8]={}; cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x; cnt[x]++;
    }
    if (cnt[5] == 0 && cnt[7] == 0 && cnt[2] >= cnt[4] &&
        cnt[1] == cnt[4] + cnt[6] && cnt[2] + cnt[3] == cnt[4] + cnt[6]) {
        for (int i = 0; i < cnt[4]; ++i) cout << "1 2 4\n";
        cnt[2] -= cnt[4];
        for (int i = 0; i < cnt[2]; ++i) cout << "1 2 6\n";
        for (int i = 0; i < cnt[3]; ++i) cout << "1 3 6\n";
    } else cout << "-1\n";
    return 0;
}