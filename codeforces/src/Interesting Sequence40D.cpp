//
// Created by Psy.C on 2025/9/25.
//
/*
 *
*ch[N] - 用于存储输入字符串的字符数组
a[N<<1], b[N<<1] - 存储大数的数组（N<<1 表示 N*2）
n, m - 记录数组 a 和 b 中数字长度的变量
 *
 *
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 310;
char ch[N];
int a[N<<1], b[N<<1], n, m;

int dmod() {
    int x(0);
    for (int i = n; i; --i) {
        x = (x << 3) + (x << 1) + a[i];
        a[i] = x / 12;
        x %= 12;
    }
    while (n > 1 && !a[n]) --n;// 移除前导零
    return x;// 返回余数
}

void mul() {
    for (int i = 1; i <= n; ++i) a[i] *= 12;
    for (int i = 1; i <= n; ++i)
        a[i + 1] += a[i] / 10, a[i] %= 10;// 处理进位
    while (a[n + 1]) {// 如需要则扩展数组
        ++n;
        a[n + 1] += a[n] / 10;
        a[n] %= 10;
    }
}

void add() {
    for (int i = 1; i <= max(n, m); ++i) {
        a[i] += b[i];
        a[i + 1] += a[i] / 10;// 进位
        a[i] %= 10;
    }
    while (a[n + 1]) {// 如需要则扩展
        ++n;
        a[n + 1] += a[n] / 10;
        a[n] %= 10;
    }
}

void dec() {
    for (int i = 1; i <= n; ++i) {
        a[i] -= b[i];
        if (a[i] < 0) {
            --a[i + 1];// 借位
            a[i] += 10;
        }
    }
    while (!a[n] && n > 1) --n;// 移除前导零
}

void dmodb() {
    int x(0);
    for (int i = m; i; --i) {
        x = (x << 3) + (x << 1) + b[i];
        b[i] = x / 12;
        x %= 12;
    }
    while (m > 1 && !b[m]) --m;
}


int main() {
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    for (int i = 1; i <= n; ++i) a[i] = (ch[n - i + 1] ^ '0');//逆序存储在数组 a 中（最低位数字在前）
    int sum(0);
    while (n > 1 || a[1]) sum += b[++m] = dmod();//余数存储在数组 b 中并求和
    if (sum != 2) puts("NO"), exit(0);

    int pos;//找到第一个非零余数的位置
    for (pos = 1; pos <= m; ++pos) if (b[pos]) break;
    int ans = m + pos - 1, ans2 = min(ans + 1 >> 1, 1000);
    puts("YES\n1");
    printf("%d\n%d\n", ans, ans2 - 1);
    n = a[1] = 1;//初始化数组 a 为1，并将其乘以12^(ans/2)，然后复制到数组 b。如果ans是偶数，则将 b 除以12
    for (int i = 1; i <= ans >> 1; ++i) mul();
    memcpy(b, a, sizeof(b));
    m = n;
    if (!(ans & 1)) dmodb();

    for (int i = 1; i <= ans2; ++i) {
        add();
        if (pos != (ans + 1 >> 1) - i + 1) {
            for (int j = n; j; --j) printf("%d", a[j]);
            puts("");
        }
        dec();
        mul();
        dmodb();
    }

    return 0;
}