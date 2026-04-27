//
// Created by Psy.C on 2026/4/26.
//
/**
a[n] = 0: 设置哨兵值，避免边界检查
i = 0: 从索引0开始
i <= n: 循环到索引n（包含哨兵位置）
++i: 每次递增1
如果a[i]是偶数，将其设为0
将a[i]设为0
检查下一个位置a[i+1]是否大于0
如果大于0，则将其减1
如果不大于0，则输出"NO"并退出程序

偶数处理: 直接消除偶数
奇数处理: 消除奇数的同时需要"借位"，即让下一个元素减1
有效性检查: 如果无法借位（下一个元素≤0），则无解
O(n)，其中n是数组长度

当i=n-1时，确保a[n]存在且值为0
当遇到奇数时，可以安全地访问a[n]并判断是否>0
由于a[n] = 0，所以a[n] > 0为假，会输出"NO"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+7;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i]; a[n] = 0;
    for (int i = 0; i <= n; ++i) {
        if (a[i]%2 == 0) a[i] = 0;
        else {
            a[i] = 0;
            if (a[i+1] > 0) a[i+1]--;
            else {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}