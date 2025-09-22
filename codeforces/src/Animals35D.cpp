//
// Created by Psy.C on 2025/9/22.
//时间复杂度：O(n log n)，主要消耗在排序上

#include <algorithm>
#include <cstdio>
using namespace std;

int a[105];
int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, x, ans = 0;// n:元素个数, x:总资源, ans:答案计数器（初始化为0）
    scanf("%d %d", &n, &x);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);// 读取第i个元素的值到a[i]
        a[i] *= (n - i + 1);// 将a[i]乘以权重(n-i+1)
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) {
        x -= a[i];// 从总资源x中减去当前元素的值
        if (x < 0) break;
        ans++;
    }
    printf("%d", ans);

    return 0;
}