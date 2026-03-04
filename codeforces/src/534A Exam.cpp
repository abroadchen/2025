//
// Created by Psy.C on 2026/3/4.
//
/**
n: 输入的数字
a[N]: 存储结果序列的数组
cnt: 当前序列中元素的计数

首先将所有奇数按顺序放入数组：1, 3, 5, 7, ...
然后尝试插入偶数，但只有当与前一个元素的差值绝对值大于1时才插入
abs(a[cnt] - i) > 1: 确保相邻元素之间的差值不为1
如果遇到差值为1的情况，停止插入

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e3+1;
int n, a[N], cnt;

int main() {
    fast;
    cin >> n;
    if (n == 4) {
        cout << "4\n";
        cout << "2 4 1 3\n";
    } else {
        for (int i = 1; i <= n; i += 2) a[++cnt] = i;
        for (int i = 2; i <= n; i += 2) {
            if (abs(a[cnt] - i) > 1) a[++cnt] = i;
            else break;
        }
        cout << cnt << '\n';
        for (int i = 1; i <= cnt; ++i) {
            cout << a[i];
            if (i == cnt) cout << '\n';
            else cout << ' ';
        }
    }
    return 0;
}