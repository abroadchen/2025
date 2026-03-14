//
// Created by Psy.C on 2026/3/13.
//
/**
计算中点位置，(n+1)>>1等价于(n+1)/2
这是1到n序列的中位数位置
如果只有一个元素(n=1)，且目标位置是1(m=1)，输出1
如果m在中点左侧，输出m+1
如果m在中点右侧，输出m-1
如果m正好在中点位置：
如果n是奇数(n%2为真)，输出m-1
如果n是偶数，输出m+1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int mid = (n + 1) >> 1;
    if (m == 1 && n == 1) cout << "1\n";
    else if (m < mid) cout << m + 1 << '\n';
    else if (m > mid) cout << m - 1 << '\n';
    else {
        if (n%2) cout << m - 1 << '\n';
        else cout << m + 1 << '\n';
    }
    return 0;
}