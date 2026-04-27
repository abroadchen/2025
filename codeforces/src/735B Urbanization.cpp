//
// Created by Psy.C on 2026/4/27.
//
/**
n：总元素数量
n1, n2：两个子集的大小
a[N]：存储输入数据的数组
t：临时累加变量
将数组前n1个最大元素求和（因为已降序排列）
计算第一个集合的平均值并存储在ans
t*1.：将整型转换为浮点型进行除法运算
重置t为0
对接下来的n2个元素求和
计算第二个集合的平均值并累加到ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7;
ll n, n1, n2, a[N], t;
int main() {
    fast;
    cin >> n >> n1 >> n2;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1, [](ll x, ll y) {
        return x > y;
    });
    if (n1 > n2) swap(n1, n2);//确保n1始终是较小的数值
    for (int i = 1; i <= n1; ++i) t += a[i];
    double ans = t*1./n1; t = 0;
    for (int i = n1+1; i <= n1+n2; ++i) t += a[i];
    ans += t*1./n2;
    printf("%.6f\n", ans);
    return 0;
}