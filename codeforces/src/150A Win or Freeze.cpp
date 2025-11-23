//
// Created by Psy.C on 2025/11/22.
//
/*
 *s: 当前待分解的数，初始化为n
 *t: 试除因子，从2开始
 */
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

int main() {
    ll n; scanf("%lld", &n);
    vector<ll> v;//存储因子的向量
    ll s(n), t(2);
    while (s > 1 && t <= static_cast<ll>(sqrt(n))) {
        if (s % t == 0) { v.push_back(t); s /= t; }//记录因子t
        else ++t;//否则尝试下一个因子
    }
    if (s > 1) v.push_back(s);//如果最后s>1，说明s是一个大于sqrt(n)的大质因子
    if (v.size() <= 1) printf("1\n0");//0个或1个因子：n是质数，输出1和0
    else if (v.size() == 2) puts("2");
    else if (v.size() > 2) printf("1\n%lld\n", v[0]*v[1]);//前两个因子的乘积
    return 0;
}