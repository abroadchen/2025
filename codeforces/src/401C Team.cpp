//
// Created by Psy.C on 2026/1/31.
//
/**
* n > m + 1：0太多，无法用1分隔（最多有m+1个位置放0）
m > (n + 1) * 2：1太多，n个0最多只能分隔2*(n+1)个1
 *
*如果n == m + 1：即0比1多1个
输出m个"01"，然后输出一个"0"
这样形成模式：010101...0，恰好有m个1和m+1个0
 *
*其他情况的构造方法：
当n == m时：输出一个'1'，消耗一个1
否则：优先输出两个'1'（"11"），如果只剩一个1则输出'1'
每轮后面跟一个'0'（只要还有0剩余）
这样确保不会有两个连续的0，且尽可能多地使用1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;//n（0的个数）和m（1的个数）
    if (n > m + 1 || m > (n + 1) * 2) cout << "-1\n";
    else if (n == m + 1) {
        for (int i = 0; i < m; ++i) cout << "01";
        cout << "0\n";
    } else {
        while (n > 0 || m > 0) {
            if (n == m) { if (m) cout << '1', --m; }
            else {
                if (m >= 2) cout << "11", m -= 2;
                else if (m == 1) cout << '1', --m;
            }
            if (n) cout << '0', --n;
        }
        cout << '\n';
    }
    return 0;
}