//
// Created by Psy.C on 2025/12/5.
//
/*
*n：项目总数
d：预算总额
a, b：价格系数
i, x, y：循环变量和临时变量
m：能购买的项目数量，初始化为0
声明配对数组c[N]用于存储项目信息
 *
*x, y：第i个项目的两个属性值
c[i].first：该项目的成本 = ax + by
c[i].second：该项目的原始编号
*按成本对项目进行排序：
从索引1到n排序（c+1表示从第二个元素开始）
pair默认按first元素升序排序，如果first相同则按second排序
 *
*按成本从低到高依次选择项目
每选择一个项目就从预算d中扣除其成本
如果预算仍然非负，计数器m加1
如果预算变为负数，停止选择
 *
*时间复杂度：O(n log n)（主要是排序的复杂度）
空间复杂度：O(n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
using namespace std;


int main() {
    fast;
    int n, d, a, b, i, x, y, m = 0;
    pair<int, int> c[N];
    cin >> n >> d >> a >> b;
    for (i = 1; i <= n; ++i) {
        cin >> x >> y;
        c[i].first = a * x + b * y;
        c[i].second = i;
    }
    sort(c + 1, c + n + 1);
    for (i = 1; i <= n; ++i) {
        d -= c[i].first;
        if (d >= 0) m++;
        else break;
    }
    cout << m << '\n';
    for (i = 1; i <= m; ++i) cout << c[i].second << ' ';
    return 0;
}