//
// Created by Psy.C on 2025/12/21.
//
/*
* 时间复杂度：O(n²) - 双重循环
空间复杂度：O(n) - dp数组和vector存储
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5002
using namespace std;


int main() {
    fast;
    int n, m, p, dp[N]; cin>>n>>m;
    vector<pair<int, double>> v;
    double x;
    for (int i = 0; i < n; ++i) {
        cin >> p >> x;
        v.emplace_back(p, x);
    }
    dp[0] = 1;//第一个元素为1
    for (int i = 1; i < n; ++i) {//最长非递减子序列
        dp[i] = 1;//每个元素至少可以构成长度为1的序列
        for (int j = 0; j < i; ++j) if (v[i].first >= v[j].first) {//当前元素的第一项大于等于之前元素的第一项
            if (dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;//更新dp[i]为更长的子序列长度
        }
    }
    const int mx = *max_element(dp, dp + n);
    cout << n - mx << '\n';//要删除的元素个数
    return 0;
}