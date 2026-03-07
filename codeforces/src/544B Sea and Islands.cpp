//
// Created by Psy.C on 2026/3/7.
//
/**
n：网格的大小（n×n网格）
k：需要放置的"L"字符数量

计算最大可放置的"L"字符数量：
如果n是偶数：x = n²/2
如果n是奇数：x = n²/2 + 1
如果需要的k大于最大可放置数量，输出"NO"并结束

i：行号
cnt：已放置的L数量
t：计数器，用于决定放置L还是S
外层循环：遍历每一行
t += n%2 == 0;：如果是偶数行，调整t的值
内层循环：遍历每一列
t++：每次递增计数器
如果t是偶数且L的数量还没达到k：放置'L'并增加计数
否则：放置'S'
每行结束后换行

在n×n网格中放置k个"L"，其余填"S"
使用奇偶性交替的策略来均匀分布"L"
x的计算公式考虑了棋盘着色的性质：
在n×n棋盘中，黑白格子的数量（类似国际象棋棋盘）
偶数n：黑白各占一半
奇数n：一种颜色比另一种多1个
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k;
int main() {
    fast;
    cin >> n >> k;
    int x = n%2 == 0 ? n*n/2 : n*n/2+1;
    if (k > x) return cout << "NO\n", 0;
    cout << "YES\n";
    for (int i = 1, cnt = 0, t = 1; i <= n; ++i) {
        t += n%2 == 0;
        for (int j = 1; j <= n; ++j) {
            t++;
            if (t%2 == 0 && cnt < k) cout << 'L', cnt++;
            else cout << 'S';
        }
        cout << '\n';
    }
    return 0;
}