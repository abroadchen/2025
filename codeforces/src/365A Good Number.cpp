//
// Created by Psy.C on 2026/1/20.
//
/**
* n（数字个数）和k（约束参数）
s[10]：标记数组，记录0-9中哪些数字出现过
cnt = 0：计数器，记录满足条件的数字个数
 *
*a：当前数字
p：当前位的数字
*循环分解数字a的每一位
p = a % 10：获取个位数字
if (p <= k) s[p] = 1：如果该位数字≤k，标记为出现过
a /= 10：去掉最后一位
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, s[10], cnt = 0; cin >> n >> k;
    for (int i = 0, a, p, j; i < n; ++i) {
        cin >> a;
        memset(s, 0, sizeof(s));
        while (a > 0) {
            p = a % 10;
            if (p <= k) s[p] = 1;
            a /= 10;
        }
        //检查0到k的每个数字是否都在当前数字a中出现过
        for (j = 0; j <= k; ++j) if (s[j] == 0) break;
        if (j > k) cnt++;//0到k的所有数字都出现了
    }
    cout << cnt << '\n';
    return 0;
}