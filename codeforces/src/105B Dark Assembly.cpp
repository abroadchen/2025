//
// Created by Psy.C on 2025/11/12.
//
/*
*n（元素个数）、k（资源总量）、a（某个参数）
声明pair数组arr，用于存储n个元素的信息，最多10个元素
 *
*定义概率计算函数prob，参数：
idx：当前处理的元素索引
r：还需要选择的元素个数
k：累积的某个值
如果r为0（不需要再选择元素），返回概率1
如果idx等于n（处理完所有元素），返回概率a/(a+k)
 *
*计算概率：
第一项：不选择当前元素的概率 = 后续选择r个元素的概率 × 不选择当前元素的概率
第二项（如果r>0）：选择当前元素的概率 = 后续选择r-1个元素的概率 × 选择当前元素的概率
返回总概率
 *
*定义深度优先搜索函数，参数：
idx：当前处理的元素索引
x：剩余可分配的资源
如果处理完所有元素，调用prob函数计算结果
 *
*枚举分配给当前元素的资源i（从0到x）：
如果分配后超过上限10，则跳出循环
将i资源分配给当前元素
递归处理下一个元素，更新最大结果
回溯，恢复原状态
 *
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

int n, k, a;
pair<int, int> arr[10];

double prob(int idx, int r, int k) {
    if (r == 0) return 1;
    if (idx == n) return (a + 0.) / (a + k + 0.);

    double res = prob(idx + 1, r, k + arr[idx].first) * (1 - arr[idx].second/10.);
    if (r) res += prob(idx + 1, r - 1, k) * (arr[idx].second/10.);
    return res;
}


double dfs(int idx, int x) {
    if (idx == n) return prob(0, n/2 + 1, 0);
    double res = 0;
    for (int i = 0; i <= x; ++i) {
        if (arr[idx].second + i > 10) break;
        arr[idx].second += i;
        res = max(res, dfs(idx + 1, x - i));
        arr[idx].second -= i;
    }
    return res;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> a;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        arr[i].second /= 10;//将第二个值除以10（可能是将百分比转换为小数）
    }
    cout << fixed << setprecision(10) << dfs(0, k) << "\n";
    return 0;
}