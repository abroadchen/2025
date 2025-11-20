//
// Created by Psy.C on 2025/11/20.
//
/*
*a：用于存储第一个输入值
b(0)：初始化为0，用于存储结果
c：用于存储第二个输入值
t(1)：初始化为1，用作权重或基数
 *
 *a|c按位或运算，当a或c任一不为0时继续循环
*c%3：c除以3的余数（0, 1, 或 2）
a%3：a除以3的余数（0, 1, 或 2）
c%3 - a%3 + 3：计算差值并加3确保非负
(c%3 - a%3 + 3) % 3：对3取模，确保结果在[0,2]范围内
* t：乘以权重t
b +=：将结果累加到b中
 *
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    ll a, b(0), c, t(1);
    for (scanf("%lld%lld", &a, &c); a|c; a/=3,c/=3,t*=3)
        b += (c%3 - a%3 + 3) % 3 * t;
    printf("%lld", b);
    return 0;
}