//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    if (n <= 2) { cout << "No\n"; return 0; }
    cout << "Yes\n";
    int len = (n+1)/2;//中间下标（约取中位数）
    cout << "1 " << len << '\n';//第一组：{1, len}
    cout << n-1;//第二组包含除 len 外的全部 n-1 个数 先输出个数 n-1，再依次输出这些数
    for (int i = 1; i <= n; i++) {
        if (i == len) continue;//跳过已放入第一组的 len
        cout << ' ' << i;
    }
    return 0;
}