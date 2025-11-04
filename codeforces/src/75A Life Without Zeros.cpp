//
// Created by Psy.C on 2025/11/4.
//
/*
*第一个while循环：
从右到左遍历x的每一位数字
如果当前位不是0，则将其添加到t的末尾
相当于去除x中的所有0，并将非零数字按原顺序组成新数字存储在t中
 *
*第二个while循环：
从右到左遍历t的每一位数字
将t的数字按逆序组成ans
相当于将t反转后存储在ans中
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;


ll conv(ll x) {
    ll t(0), ans(0);
    while (x > 0) { if (x % 10) t = 10*t+x%10; x /= 10; }
    while (t > 0) { ans = 10*ans+t%10; t /= 10; }
    return ans;
}


int main() {

    ll a, b; scanf("%lld%lld",&a,&b);
    (conv(a) + conv(b) == conv(a + b)) ? puts("YES") : puts("NO");
    return 0;
}