//
// Created by Psy.C on 2025/11/14.
//
/*
*内层循环遍历所有可能的因子j，条件是j*j <= x（只需要检查到sqrt(x)）
如果j不是x的因子，则跳过
计算另一个因子b = x/j（因为如果j是因子，那么x/j也是因子）
检查v[j]是否小于i-y：
如果是，说明j这个因子在之前的i-y次操作中没有出现过，计数器加1
更新v[j]为当前操作次数i
对b执行同样的检查和更新操作
 *
 *v[d]：记录因子d最后一次出现的操作编号
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1e5+7;

int main() {
    vector<int> v(N, 0);
    int n; scanf("%d",&n);

    for (int i = 1, x, y; i <= n; ++i) {
        scanf("%d%d",&x,&y); int cnt = 0;
        for (int j = 1; j * j <= x; ++j) {
            if (x % j != 0) continue;
            int b = x / j;
            if (v[j] < i - y) cnt++; v[j] = i;
            if (v[b] < i - y) cnt++; v[b] = i;
        }
        printf("%d\n",cnt);
    }
    return 0;
}