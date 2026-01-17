//
// Created by Psy.C on 2026/1/17.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
using namespace std;

///找到最大的p值，使得对于所有a[i]，都有a[i] % p <= k
int main() {
    fast;
    int n, k, a[N]; cin >> n >> k;
    int p = 1e9 + 7;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        p = min(p, a[i]);//当前最小值
    }
    bool flag = true;
    while (flag) {
        flag = false;//循环开始时重置
        for (int i = 1; i <= n; ++i) {//遍历所有数组元素
            while (a[i] % p > k) p--, flag = true;//表示还需要继续循环
        }
    }
    cout << p;
    return 0;
}