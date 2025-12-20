//
// Created by Psy.C on 2025/12/20.
//
/*
*树状数组的查询操作
查询在位置x之前的元素中，tr数组的最大值
x & -x获取x的最低位1所代表的值
时间复杂度O(log x)
*树状数组的更新操作
在位置x处更新值为val，并维护tr数组的正确性
向上更新所有相关节点
 *
 *k(测试用例数)、n(序列长度)、mx(最大值)、t(阈值)
*统计不同元素的个数cnt
用布尔数组a标记元素是否出现过
 *如果不同元素个数不超过阈值t，直接输出cnt并继续下一个测试用例
*双重循环：外层循环t次，内层遍历序列
query(b[i] - 1) + 1：查询小于b[i]的位置中，最长上升子序列的长度加1
如果新长度大于f[i]，则更新：
f[i] = x：更新位置i处的最长长度
update(b[i], x)：在树状数组中更新位置b[i]的值
ans = max(ans, x)：更新全局最大值
 *
 *时间复杂度：O(t × n × log(mx))
 *
 *
 *
*对向量v排序并去重，实现离散化
如果不同元素个数不超过m，直接输出个数并继续下一个测试用例
 *将原数组a中的元素映射为离散化后的索引值(从1开始)
 *初始化数组f为0，f[i]表示以离散化值i结尾的最长上升子序列长度
 *
*循环n*m次处理元素
a[i%n]循环使用原数组中的元素
cur = f[a[i%n]-1] + 1：计算以当前元素结尾的可能最长长度
从当前位置向后更新f数组：如果f[j]小于cur，则更新f[j]为cur，否则跳出循环
如果已经达到理论最大值则提前结束

减1是因为离散化后的值从1开始，而数组索引从0开始
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100100
using namespace std;

int main() {
    fast;
    int T, n, lim, m, a[N], f[N];
    cin >> T >> n >> lim >> m;
    vector<int> v;
    while (T--) {
        v.clear();
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            v.push_back(a[i]);
        }
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        if (v.size() <= m) { cout << v.size() << '\n'; continue; }
        for (int i = 0; i < n; ++i) a[i] = static_cast<int>(lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1);
        for (int i = 1; i <= v.size(); ++i) f[i] = 0;
        for (int i = 0; i < n * m; ++i) {
            const int cur = f[a[i%n]-1] + 1;
            for (int j = a[i%n]; j <= v.size(); ++j) {
                if (f[j] < cur) f[j] = cur; else break;
            }
            if (f[v.size()] == v.size()) break;
        }
        cout << f[v.size()] << '\n';
    }
    return 0;
}