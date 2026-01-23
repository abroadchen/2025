//
// Created by Psy.C on 2026/1/23.
//
/**
* a: 账户数量（或账户范围0到a）
b: 交易次数
*mp[N]: 数组跟踪每个账户的余额变化（初始全为0）
sum: 存储最终结果（总正余额）
 *
*循环处理b笔交易
每笔交易：将金额e从账户c转移到账户d
mp[c] -= e: 减少源账户c的余额
mp[d] += e: 增加目标账户d的余额
 *
*遍历从0到a的所有账户
累加所有正余额
只有正余额（> 0）的账户计入总和
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10005
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    int mp[N]={}, sum = 0;
    for (int i = 0, c, d, e; i < b; ++i) {
        cin >> c >> d >> e;
        mp[c] -= e; mp[d] += e;
    }
    for (int i = 0; i <= a; ++i) if (mp[i] > 0) sum += mp[i];
    cout << sum;
    return 0;
}