//
// Created by Psy.C on 2025/12/8.
//
/*
*n：序列长度
k：参数
lst：上一个元素的值，初始为0
cnt：连续相同元素的计数，初始为0
 *
*循环n次，读取序列中的每个元素a
如果当前元素a等于上一个元素lst：
连续计数cnt加1
否则（当前元素与上一个不同）：
重置连续计数cnt为1
更新lst为当前元素a的值
 *
*如果cnt + k > n（连续相同元素长度+k超过总长度）：
输出n - cnt（剩余需要改变的元素个数）
否则：
输出-1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, lst = 0, cnt = 0; cin >> n >> k;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        if (a == lst) cnt++;
        else cnt = 1;
        lst = a;
    }
    cout << (cnt + k > n ? n - cnt : -1) << '\n';
    return 0;
}