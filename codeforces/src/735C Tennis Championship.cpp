//
// Created by Psy.C on 2026/4/27.
//
/**
初始化a[0]=0, a[1]=1，其余元素默认为0
从1到90遍历查找
找到第一个使得n < a[i]成立的位置
输出i-1并结束程序
如果前面的循环没有找到满足条件的位置，输出90

预处理：O(1)，因为循环次数固定为90
查询：O(1)，最坏情况下遍历90次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a[91] = {0, 1}, n;
int main() {
    fast;
    for (int i = 2; i <= 90; ++i)
        a[i] = a[i-1] + a[i-2] + 1;
    cin >> n; n -= 1;
    for (int i = 1; i <= 90; ++i)
        if (n < a[i]) {
            cout << i-1 << '\n';
            return 0;
        }
    cout << "90" << '\n';
    return 0;
}