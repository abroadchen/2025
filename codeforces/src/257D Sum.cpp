//
// Created by Psy.C on 2025/12/19.
//
/*
 *当前累计值大于等于当前元素
 *减去当前元素
 *标记为负号
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500050
using namespace std;


int main() {
    fast;
    int n, pre[N]; cin>>n; ll sum = 0, a[N];
    for (int i = 1; i <= n; ++i) cin>>a[i];
    for (int i = n; i >= 1; --i) {
        if (sum >= a[i]) { sum -= a[i]; pre[i] = -1; }
        else { sum = a[i] - sum; pre[i] = 1; }
    }
    pre[0] = -1;//初始化前一个状态为负号
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i] * (-pre[i-1]);//确定实际符号
        if (pre[i] == 1) cout << '+'; else cout << '-';
    }
    return 0;
}