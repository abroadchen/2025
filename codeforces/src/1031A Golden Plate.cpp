//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
输入矩形的长 n、宽 m，以及要剥离的层数 k
第 i 层（从 0 开始）剥离后，剩下矩形的长宽各缩了 i*2*2 = 4i（每剥一层，长和宽各向内缩 2，共 4）。
当前层矩形的周长 = (len+w)*2 - 4。
(len+w)*2：完整矩形周长。
-4：因为四个角在求和时会重复计算，每圈多算 4 个单位（角点）
输出所有圈周长之和。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, m, k, ans;
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        int len = n - i*2*2, w = m - i*2*2;
        ans += (len+w)*2 - 4;
    }
    cout << ans << '\n';
    return 0;
}