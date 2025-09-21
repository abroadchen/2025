//
// Created by Psy.C on 2025/9/21.
//

#include <algorithm>
#include <cstdio>
using namespace std;

int main() {

    int n(0), m(0); scanf("%d %d", &n, &m);// 读取数组长度n和要选择的元素数量m
    int* price = new int[n];
    for (int i = 0; i < n; ++i) scanf("%d",&price[i]);
    sort(price, price + n);

    long ans(0);// 初始化总收益为0
    for (int i = 0; i < m; ++i) {// 选择前m个最小的价格（贪心策略）
        if (price[i] < 0) ans -= price[i];// 负负得正，相当于获得收益
        else break;
    }
    printf("%ld\n", ans);

    return 0;
}