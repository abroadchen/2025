//
// Created by Psy.C on 2025/11/9.
//
/*
*读取第i个元素的值存储在a[i].first
将原始索引i存储在a[i].second
这样每个pair包含了(值, 原始位置)
 *对向量a按first（值）进行升序排序，second（原始位置）保持对应关系
 *
*mx：记录到目前为止遇到的最大原始位置索引
f：结果数组，f[i]表示原位置i的元素需要移动的距离
对排序后的每个元素进行处理：
a[i].second：当前元素的原始位置
如果当前元素的原始位置大于之前遇到的最大位置(a[i].second > mx)，说明它已经在正确的位置或右侧，不需要向左移动，设为-1
否则，计算需要向左移动的距离：mx - a[i].second - 1
更新最大位置：mx = max(mx, a[i].second)
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    int mx(-1);
    vector<int> f(n);
    for (int i = 0; i < n; ++i) {
        f[a[i].second] = (a[i].second > mx) ? -1 : mx - a[i].second - 1;
        mx = mx > a[i].second ? mx : a[i].second;
    }
    for (int i = 0; i < n; ++i) printf("%d ", f[i]);
    printf("\n");
    return 0;
}