//
// Created by Psy.C on 2026/3/2.
//
/**
c：总容量/预算
ha, hb：类型A和类型B的收益值
wa, wb：类型A和类型B的消耗值
ans：最大收益答案

规范化：确保wb ≥ wa（B类消耗更大）
交换属性：如果A类消耗更大，则交换A、B的属性

如果B类消耗大于√c
枚举B类数量：i从0到c/wb（最多能选多少个B类）
收益计算：i*hb是B类收益，(c-i*wb)/wa*ha是剩余容量选A类的收益
更新答案：取最大收益

ha*1./wa > (hb*1./wb) 比较单位消耗的收益
重新规范：如果A类性价比更高，则交换A、B的属性
枚举A类数量：i从0到wb（循环上界为wb）
收益计算：i*ha是A类收益，(c-i*wa)/wb*hb是剩余容量选B类的收益

第一种情况：O(√c)
第二种情况：O(√c)（因为wb ≤ √c）
根号分治的优化技巧
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll c, ha, hb, wa, wb, ans;
int main() {
    fast;
    cin >> c >> ha >> hb >> wa >> wb;
    if (wa > wb) swap(wa, wb), swap(ha, hb);
    if (wb > sqrt(c)) {
        for (int i = 0; i <= c/wb; ++i)
            ans = max(ans, i*hb + (c-i*wb)/wa*ha);
    } else {
        if (ha*1./wa > (hb*1./wb))
            swap(wa, wb), swap(ha, hb);
        for (int i = 0; i <= wb; ++i)
            ans = max(ans, i*ha + (c-i*wa)/wb*hb);
    }
    cout << ans << '\n';
    return 0;
}