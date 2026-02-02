//
// Created by Psy.C on 2026/2/2.
//
///x/p[k]：计算当前约束下的最大可执行次数
/**
* x：第k种资源的总量
p[k]：第k种资源的单位需求量
*ans = min(x[0]/p[0], x[1]/p[1], ..., x[4]/p[4])
最大执行次数受最稀缺资源的限制
*时间复杂度：O(1)（固定5次循环）
空间复杂度：O(1)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int p[] = {1,1,2,7,4};//系数

int main() {
    fast;
    int ans(100);
    for (int k = 0, x; k < 5; ++k) {
        cin >> x;
        if (ans > x/p[k]) ans = x/p[k];//更新最小值
    }
    cout << ans << '\n';
    return 0;
}