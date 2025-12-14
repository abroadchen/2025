//
// Created by Psy.C on 2025/12/13.
//
/*
 *
*计算初始x值：x = k - y % k
y % k是y除以k的余数
k - y % k是使y+x能被k整除的最小正数
top = n - y是x的最大值（因为y+x ≤ n）
 *
*如果初始x不超过最大值top：
输出第一个x值
然后依次输出x+k, x+2k, x+3k...直到超过top
否则输出"-1"表示无解
 *
 *O((n-y)/k) - 最多输出(n-y)/k个数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int y, k, n; cin >> y >> k >> n;
    int x = k - y % k;
    const int top = n - y;
    if (x <= top) {
        cout << x;
        x += k;
        while (x <= top) {
            cout << ' ' << x;
            x += k;
        }
        cout << '\n';
    } else cout << "-1\n";
    return 0;
}