//
// Created by Psy.C on 2025/11/10.
//
/*
 *l和r，表示区间的左右端点
 *
 *dfs，接受两个整数参数x和y，返回x的y次方对mod取模的结果
 *递归终止条件：如果y为0，返回1（任何数的0次方都等于1）
 *递归计算x的(y/2)次方，y>>1是位运算，相当于y/2
 *x^y = (x^(y/2))^2，将结果平方并对mod取模
 *如果y是奇数，需要再乘以一个x，因为x^y = (x^(y/2))^2 * x（当y为奇数时）
 *
 *dfs(2, mod-2)是计算2的模逆元
 *计算区间[l,r]的结果，通过前缀和相减得到
 */
#include <cstdio>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
int l, r;
ll ret;


ll dfs(int x, int y) {
    if (!y) return 1;
    ll ret = dfs(x, y>>1);
    ret = ret * ret % mod;
    if (y & 1) ret = ret * x % mod;
    return ret;
}

ll f(int x) {
    if (!x) return 0;
    if (x == 1) return 4;
    if (x & 1) return (33 * dfs(3, x/2-1)-7) % mod;
    return (19 * dfs(3, x/2-1)-7) % mod;
}


ll calc(int len) {
    return (f(len) + f(len+1>>1)) % mod *
        dfs(2, mod - 2) % mod;
}

int main() {
    scanf("%d%d", &l, &r);
    ret = calc(r) - calc(l-1);
    if (ret < 0) ret += mod;
    printf("%lld\n", ret);
    return 0;
}