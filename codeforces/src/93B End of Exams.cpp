//
// Created by Psy.C on 2025/11/9.
//
/*
*n：资源总量（或某种单位数量）
w：总权重（或总价值）
m：接收者数量
 *
 *当n<m时，需要将m个接收者分成若干组，每组共享资源，每组大小为(m-n)，如果不能整除则无法分配
 *
*外层循环：遍历每个接收者(i从1到m)
内层循环：为当前接收者分配资源直到满足需求
sum：当前接收者已获得的资源总量
cnt：本次分配的资源量，取所需资源和可用资源的最小值
更新已使用量和已分配总量
输出：资源块编号和分配的权重值(cnt/m*w)
如果当前资源块用完，切换到下一个资源块
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

int n, w, m;

int main() {
    scanf("%d%d%d", &n, &w, &m);
    if (n < m && m % (m - n) > 0) return puts("NO"), 0;
    puts("YES");
    int cur(1), used(0);
    for (int i = 1; i < m + 1; ++i) {
        int sum = 0;
        for (int j = 0; sum < n; ++j) {
            int cnt = min(n - sum, m - used);
            used += cnt; sum += cnt;
            if (j) putchar(' ');
            printf("%d %.16f", cur, (double)cnt / m * w);
            if (used == m) cur++, used = 0;
        }
        puts("");
    }
    return 0;
}