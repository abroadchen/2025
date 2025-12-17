//
// Created by Psy.C on 2025/12/17.
//
/*
 *
*计算从(1,1)到(x,y)区域内所有min(i,j)的和：
如果x>y：计算较大x范围内的贡献
如果x≤y：计算较大y范围内的贡献
使用了数学公式优化计算，避免逐个枚举
 *
*递归输出数字的后10位：
cnt计数防止输出超过10位
递归到最深层后再逐层返回输出，实现从高位到低位的输出
*普通数字输出函数：
递归处理高位数字
当x为0且f为true时输出'0'（处理输入为0的情况）
 *
 *容斥原理：S(c,d) - S(a-1,d) - S(c,b-1) + S(a-1,b-1)，其中S(x,y)表示从(1,1)到(x,y)的和
 *
 *
 */
#include <iostream>
#define ll __int128
using namespace std;

ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x<<3) + (x<<1) + (ch - '0');
        ch = getchar();
    }
    return x * f;
}

ll c(const ll x) {//1²+2²+3²+...+x² = x(x+1)(2x+1)/6
    if (x == 0) return 0;
    return x * (x + 1) * (2 * x + 1) / 6;
}

ll get(const ll x, const ll y) {
    ll res = 0;
    if (x > y) {
        res += (y * y + 1) * y * y / 2;
        const ll cnt = c(x) - c(y);
        res += cnt * y;
        res = res - (x - y) * y * (y - 1) / 2;
    } else {
        res = (x * x + 1) * x * x / 2;
        const ll cnt = c(y - 1) - c(x - 1) + y - x;
        res += cnt * x;
        res = res + (y - x) * x * (x - 1) / 2;
    }
    return res;
}

void out(const ll x, int cnt) {
    if (cnt == 11) return;
    out(x / 10, ++cnt);
    putchar('0' + x % 10);
}
void out2(const ll x, const bool f) {
    if (x) {
        out2(x / 10, false);
        putchar('0' + x % 10);
    } else if (f) putchar('0');
}

int main() {
    ll t = read();
    while (t--) {
        const ll a = read(), b = read(),  c = read(),  d = read(),
        ans = ((get(c, d) - get(a - 1, d)) - get(c, b - 1)) +
            get(a - 1, b - 1);
        if (ans >= 10000000000ll) {
            printf("..."); out(ans, 1);
        } else out2(ans, true);
        printf("\n");
    }
    return 0;
}