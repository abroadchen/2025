//
// Created by Psy.C on 2026/9/15.
//
/**
1. (x+k-1)/k — 向上取整

整数除法 x/k 是向下取整。(x+k-1)/k 是向上取整（ceiling）的经典写法：

把 x 除以 k 的结果向上取整。
例如 k=3：x=1→1，x=3→1，x=4→2，x=7→3。
含义：把 x 个东西按每份最多 k 个打包，需要的最少包数。

2. 累加到 sum

对每组输入的 n 个数 x，把每个 (x+k-1)/k 累加，得到 sum = 总共需要的包/份数总和。

3. (sum+1)/2 — 向上取整的一半

sum 除以 2 再向上取整：

sum=4 → (4+1)/2=2
sum=5 → (5+1)/2=3
sum=1 → (1+1)/2=1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, x;
    while (cin >> n >> k) {
        int sum = 0;
        while (n--) {
            cin >> x;
            sum += (x+k-1)/k;
        }
        cout << (sum+1)/2 << '\n';
    }
    return 0;
}