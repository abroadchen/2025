//
// Created by Psy.C on 2025/11/25.
//
/*
 *ans 当前子序列和 mx 最大和（初始化为极小值）
 *
 *j, j+i, j+2*i, j+3*i, ..., j+(n/i-1)*i
 *
*外层循环：O(n/3)
中层循环：O(i)
内层循环：O(n/i)
总体复杂度：O(∑(i × n/i)) = O(∑n) = O(n × d(n))
其中d(n)是n的约数个数，通常很小
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> v(n);//存储输入数组
    for (int i = 0; i < n; ++i) cin >> v[i];
    int ans = 0, mx = -3e7;
    for (int i = 1; i <= n / 3; ++i) {//枚举间隔i
        if (n % i != 0) continue;//只考虑能整除n的间隔
        for (int j = 0; j < i; ++j) {//枚举起始位置j
            ans = 0;
            for (int k = 0; k < n / i; ++k) ans += v[i * k + j];//计算子序列和
            if (ans > mx) mx = ans;//更新最大值
        }
    }
    cout << mx << '\n';
    return 0;
}