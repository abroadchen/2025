//
// Created by Psy.C on 2025/11/7.
//
/*
*对每一位数字进行反射变换：d → (9-d)
例如：1→8, 2→7, 3→6, 等等
 *
 *时间复杂度为O(log r)
 *
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef long long ll;

ll reflect(ll n) {
    char s[20];
    sprintf(s, "%lld", n);//将数字n转换为字符串格式
    int len = strlen(s);
    for (int i = 0; i < len; ++i) s[i] = '0' + (9 - (s[i] - '0'));
    return atoll(s);//将变换后的字符串转换回长整数并返回
}
ll max(ll a, ll b) { return a > b ? a : b; }

int main() {
    ll l, r; scanf("%lld %lld", &l, &r);
    ll res(0);
    res = max(res, l * reflect(l));
    res = max(res, r * reflect(r));

    ll p(1);
    while (p <= r) {
        ll mid = p * 5 - 1;//计算关键中间值（如4, 49, 499, 4999...）
        if (mid >= l && mid <= r) res = max(res, mid * reflect(mid));
        for (ll i = -2; i <= 2; ++i) {//检查mid附近的数
            ll c = mid + i;
            if (c >= l && c <= r) res = max(res, c * reflect(c));
        }
        p *= 10;//处理更高位数的情况
    }
    printf("%lld\n", res);
    return 0;
}