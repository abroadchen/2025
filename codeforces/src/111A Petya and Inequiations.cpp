//
// Created by Psy.C on 2025/11/14.
//
/*
 *n(元素个数)、x(平方和的目标值)、y(总和的目标值)
 *
*初始化标志变量p为true(表示可以构造成功)
创建一个大小为n的向量num，所有元素初始化为1
将最后一个元素设置为y - (n-1)，这样前n-1个元素都是1，最后一个元素补足总和为y
如果最后一个元素小于等于0，说明无法构造(因为要求正整数)，将标志设为false
*计算当前构造数组的平方和
如果平方和小于目标值x，说明不满足条件，将标志设为false
*如果标志为true(可以构造)，输出构造的数组
否则输出-1表示无法构造
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    ll n, x, y; scanf("%lld %lld %lld", &n, &x, &y);
    bool p = 1;
    vector<ll> num(n, 1);
    num[n - 1] = y - (n - 1);
    if (num[n - 1] <= 0) p = 0;

    ll sum = 0;
    for (int i = 0; i < n; ++i) sum += num[i] * num[i];
    if (sum < x) p = 0;

    if (p) {
        for (int i = 0; i < n; ++i) printf("%lld ", num[i]);
        printf("\n");
    } else puts("-1");
    return 0;
}