//
// Created by Psy.C on 2026/3/11.
//
/**
b: 男选手数量
g: 女选手数量（或总奖金/限制）
a[N]: 存储处理后的能力值数组
p: 权重因子（初始化为1.0）

读入2*b个能力值（可能包括男选手和女选手）
将每个值乘以权重因子p（目前p=1.0，所以实际没改变）
对能力值进行升序排序
a[1]: 最小的能力值
a[b+1]/2: 第(b+1)小的能力值除以2
sum = min(a[1], a[b+1]/2): 取两者的最小值
ans = min(sum*3*b, g*p): 最终答案是两个值的最小值

选择策略:
a[1]: 最弱选手的能力值
a[b+1]/2: 中等强度选手能力值的一半
选择两者中较小的作为基础评分
约束处理:
sum*3*b: 基础评分乘以总权重
g*p: 上限约束
取两者的最小值

排序: O(n log n)，其中n = 2*b
其他操作: O(1)
总体: O(b log b)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int b, g;
double a[N], p = 1.0000000;
int main() {
    fast;
    cin >> b >> g;
    for (int i = 1; i <= 2*b; ++i) {
        cin >> a[i]; a[i] *= p;
    }
    sort(a + 1, a + 2*b + 1);
    double sum = min(a[1], a[b+1]/2), ans = min(sum*3*b, g*p);
    cout << setprecision(7) << ans << '\n';
    return 0;
}