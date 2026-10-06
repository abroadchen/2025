//
// Created by Psy.C on 2026/10/6.
//
/**
打印了"偶数段 + 奇数段 + 偶数段"三段，偶数每段约 n/2 个，奇数段约 n/2 个（向上取整），所以总长 = 偶数段 ×2 + 奇数段 = (n/2)*2 + (n+1)/2 ≈ n + n/2。这是一个长度为 n + n/2 的序列（不是简单的 n 的排列，而是带重复、更长的一个构造）。
第一段：从 2 到 n 的所有偶数。
第二段：从 1 到 n 的所有奇数。
第三段：再次打印从 2 到 n 的所有偶数。
三段之间用空格分隔，末尾也有空格

坦克两条命，三次最优必死光。

坦克被打会动，所以每次起始位置不一样，2,1,2

炸了后有坦克的地区中间一格为空，所以i+=2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    cout << n+n/2 << '\n';//先输出一个
    for (int i = 2; i <= n; i += 2) cout << i << ' ';//第一回炸
    for (int i = 1; i <= n; i += 2) cout << i << ' ';//第二回炸，炸的都是有了坦克的地方
    for (int i = 2; i <= n; i += 2) cout << i << ' ';//被炸后移动，炸移动后位置
    return 0;
}