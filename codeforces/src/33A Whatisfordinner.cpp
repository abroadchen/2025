//
// Created by Psy.C on 2025/9/21.
//

#include <cstdio>
using namespace std;

int main() {
    // 读取n(项目数)、m(类别数)、k(预算上限)
    long n(0), m(0), k(0); scanf("%ld %ld %ld", &n, &m, &k);
    long* viablility = new long[m + 1];// 动态分配数组，存储每类的最小成本

    const long maxV = 1000000;
    for (long i = 1; i <= m; ++i) viablility[i] = maxV;

    for (int i = 0; i < n; ++i) {// 读取项目类别cur和成本cur2
        long cur(0), cur2(0); scanf("%ld %ld", &cur, &cur2);
        // 更新该类别的最小成本（贪心策略）
        if (cur2 < viablility[cur]) viablility[cur] = cur2;
    }

    long ans(0);
    for (long i = 1; i <= m; ++i) ans += viablility[i];
    printf("%ld\n", ans < k ? ans : k);// 输出结果：取总成本和预算上限中的较小值
    return 0;
}