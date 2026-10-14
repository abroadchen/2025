//
// Created by Psy.C on 2026/10/14.
//
/**
每组 n % i == i-1 等价于 (n+1) % i == 0，即 i | (n+1)。

所以整道题等价于判定：

lcm(1,2,...,k) 是否整除 n+1（即 n+1 是 1..k 的公倍数
if (!n && !k) return 1;：处理多组数据的终止条件——当读到 n=0, k=0 时退出程序。这里返回 1（非零），结合用 while 读入的话通常应返回 0，初学者常用此写法示意"结束输入"。注意：这段代码本身没有 while 循环来读多组，所以此判断仅在单次输入时用于合法性检查（n=k=0 属于非法/空输入）。
循环逐 i 判定：从 1 到 k 遍历，若某个 i 使 n % i != i-1，直接输出 "No" 并结束。
若所有 i 都满足，则输出 "Yes"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k;
int main() {
    fast;
    cin >> n >> k;
    if (!n&&!k) return 1;
    for (int i = 1; i <= k; ++i)
        if (n%i != i-1) return cout << "No\n", 0;
    cout << "Yes\n";
    return 0;
}