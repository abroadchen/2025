//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3007
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    unsigned joy[N][3], dp[2][2];
    for (int i = 0; i < n; ++i) cin >> joy[i][0];//读取第一行快乐值
    for (int i = 0; i < n; ++i) cin >> joy[i][1];
    for (int i = 0; i < n; ++i) cin >> joy[i][2];
    int x = 0;//当前状态的索引
    //第i个元素选择第0种方式获得的最大快乐值
    //第i个元素选择第1种方式获得的最大快乐值
    dp[0][0] = joy[0][0], dp[0][1] = joy[0][1];
    for (int i = 2; i <= n; ++i) {
        //计算新状态0
        //当前选择方式0，前一个可以选择方式0（+joy[i-1][1]）或方式1（+joy[i-1][0]）
        dp[!x][0] = max(dp[x][0] + joy[i-1][1], dp[x][1] + joy[i-1][0]);
        dp[!x][1] = max(dp[x][0] + joy[i-1][2], dp[x][1] + joy[i-1][1]);
        x = !x;//切换状态索引（0变1，1变0），实现滚动数组优化
    }
    cout << dp[x][0] << '\n';
    return 0;
}