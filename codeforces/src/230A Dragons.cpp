//
// Created by Psy.C on 2025/12/10.
//
/*
*s: 初始力量值
n: 龙的数量
i: 循环变量
flag: 标志变量，初始化为1表示成功，0表示失败
 *
*a[i].first: 第i条龙的力量值（需要击败它所需的力量）
a[i].second: 击败第i条龙后获得的力量奖励
 *
*如果当前力量值s小于等于第i条龙的力量值a[i].first，说明无法击败这条龙，设置flag为0并跳出循环
否则，击败这条龙，将获得的力量奖励a[i].second加到当前力量值s上
 *
*时间复杂度: O(n log n)，主要消耗在排序上
空间复杂度: O(n)，用于存储龙的信息
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000
#define ii pair<int,int>
using namespace std;


int main() {
    fast;
    int s, n, i, flag = 1; cin>>s>>n;
    ii a[N];
    for (i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a, a+n);
    for (i = 0; i < n; ++i) {
        if (s <= a[i].first) { flag = 0; break; }
        s += a[i].second;
    }
    if (flag == 0) cout << "NO\n";
    else cout << "YES\n";
    return 0;
}