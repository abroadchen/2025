//
// Created by Psy.C on 2025/12/7.
//
/*
*a[N]：辅助数组，用于记录覆盖情况
ans[N]：结果数组，存储构造的数组元素
读取三个参数：n（数组长度相关）、m（范围限制）、k（重复次数）
 *
*当m ≤ n-2时：
输出数组长度：2*k
构造方案：k个1，1个n，k-1个(n+1)
这样构造确保了某些特定的数学性质
*当m > n-2时：
cnt初始化为k+1，用于记录结果数组的当前位置
遍历从1到m的每个位置：
如果位置i已经被覆盖k次，跳过
如果位置i还未被覆盖（a[i]==0）：
在结果数组中添加i-1
更新覆盖计数数组a，从位置i开始的n-1个位置都增加1
计算还需要增加的覆盖次数w = k - a[i]
从位置i开始的n个位置都增加w次覆盖
在结果数组中添加w个i

*如果位置m+1没有被覆盖，在结果数组中添加m
输出结果数组长度：cnt-1
输出结果：前k个元素是1，后面的元素是ans[i]+n
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000
using namespace std;

int a[N], ans[N];

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    if (m <= n - 2) {
        cout << 2 * k << '\n';
        for (int i = 0; i < k; ++i) cout << "1 ";
        cout << n << ' ';
        n++;
        for (int i = 1; i < k; ++i) cout << n << ' ';
        cout << '\n';
    } else {
        int cnt = k + 1;
        for (int i = 1; i <= m; ++i) {
            if (a[i] == k) continue;
            if (a[i] == 0) {
                ans[cnt++] = i - 1;
                for (int j = 0; j < n - 1; ++j) a[i+j]++;
            }
            const int w = k - a[i];
            for (int j = 0; j < n; ++j) a[i+j] += w;
            for (int j = 0; j < w; ++j) ans[cnt++] = i;
        }
        if (a[m+1] == 0) ans[cnt++] = m;
        cout << cnt - 1 << '\n';
        for (int i = 0; i < k; ++i) cout << "1 ";
        for (int i = k + 1; i < cnt; ++i) cout << ans[i] + n << ' ';
        cout << '\n';
    }
    return 0;
}