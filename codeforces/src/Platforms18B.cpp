//
// Created by Psy.C on 2025/9/17.
//
/*
*n: 建筑物数量
d: 桥梁长度
m: 建筑物间距参数
l: 建筑物长度参数
 *
*计算b = m * a + l + d：这是第a个建筑物右侧边缘加上桥梁长度的位置
计算b - b % d：这是不大于b且能被d整除的最大数，即桥梁右端点可能的最远位置
将ans更新为这个位置
检查这个位置是否小于下一个建筑物的起始位置m * (a + 1)
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int64_t n, d, m, l; cin >> n >> d >> m >> l;
    int64_t ans(0);
    for (int64_t a = 0; a < n; ++a) {
        int64_t b = m * a + l + d;
        ans = b - b % d;
        if (b - b % d < m * (a + 1)) break;
    }
    cout << ans << endl;
    
    return 0;
}