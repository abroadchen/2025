//
// Created by Psy.C on 2026/2/13.
//
/**
当x为1时： r++ - 增加当前连续1的计数

当x为0时：

如果当前有连续的1（r > 0）：
g++ - 增加组数计数（一段连续的1算作一组）
ans += r - 1 - 累加当前连续1段的贡献（连续n个1贡献n-1）
r = 0 - 重置连续1计数器
如果循环结束后还有未处理的连续1段（末尾以1结尾）
增加组数计数并累加贡献
如果没有连续1的组： 输出0

如果有连续1的组： 输出 ans + ((g-1)<<1) + 1

ans：处理每组内部连续1的代价
2*g - 1：处理g组连续1和g-1个间隔的代价
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, ans, r, g;

int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x) r++; else {
            if (r) {
                g++;
                ans += r - 1;
            }
            r = 0;
        }
    }
    if (r) { g++; ans += r - 1; }
    if (!g) cout << '0';
    else cout << ans + ((g-1)<<1) + 1 << '\n';
    return 0;
}