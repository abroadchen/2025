//
// Created by Psy.C on 2025/9/17.
//
/*
*N: 最大数组大小(2,000,005)
mod: 模数(51,123,987)
inv2: 2在模mod下的逆元(25,561,994)

 *
*n: 字符串长度
ori[N]: 原始字符串数组
s[N<<1]: Manacher算法处理后的字符串数组(大小为2N)
p[N<<1]: Manacher算法中每个位置的回文半径
l[N<<1], r[N<<1]: 差分数组，记录回文覆盖范围
left[N], right[N]: 每个位置左侧和右侧的回文计数
ans: 最终答案
 *
 *
*使用位运算优化：x<<1是2x，x<<3是8x，所以(x<<1)+(x<<3)=10x
s^48将字符转换为数字('0'的ASCII码是48)
 *
*s[0] = -1: 字符串开始标记
s[1] = -3: 分隔符
在每个原始字符间插入分隔符-3
s[j] = -2: 字符串结束标记
返回处理后字符串的长度
 *
*初始化处理字符串
R: 当前最右回文边界，mid: 对应中心
利用回文的对称性质优化计算
p[i]: 以i为中心的回文半径
扩展回文并更新最右边界
 *
 *将字符转换为0-25的数字存储在ori中
 *
*l数组记录以每个位置为起点的回文数量
r数组记录以每个位置为终点的回文数量

 *
*计算总回文数：p[i]>>1是以i为中心的回文个数
前缀和计算差分数组得到实际计数
提取原始字符串位置的left和right数组
 *
*从右到左累加left数组
计算所有回文对的数量：C(ans,2) = ans*(ans-1)/2
 *减去不相交的回文对数量
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = 2e6 + 5, mod = 51123987, inv2 = 25561994;
int n, ori[N], s[N << 1], p[N << 1], l[N << 1], r[N << 1], left[N], right[N];
long long ans;

int read() {
    int x = 0, f = 1; char s;
    while ((s = getchar()) > '9' || s < '0') {
        if (s == '-') f = -1;
        if (s == EOF) exit(0);
    }
    while (s <= '9' && s >= '0') {
        x = (x << 1) + (x << 3) + (s ^ 48);
        s = getchar();
    }
    return x * f;
}

int init() {
    s[0] = -1; s[1] = -3;
    int j = 2;
    for (int i = 0; i < n; ++i) {
        s[j++] = ori[i];
        s[j++] = -3;
    }
    s[j] = -2;
    return j;
}


void manacher() {
    n = init();
    int R = 0, mid;
    for (int i = 1; i < n; ++i) {
        if (i < R) p[i] = min(p[(mid << 1) - i], R - i);
        else p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]]) ++p[i];
        if (R < i + p[i]) {
            R = i + p[i];
            mid = i;
        }
    }
}

long long fix(const long long x) {
    return (x % mod + mod) % mod;
}

int main() {
    char ch[N]; int tmp;
    n = read(); scanf("%s", ch);
    for (int i = 0; i < n; ++i) ori[i] = ch[i] - 'a';
    tmp = n;
    manacher();

    for (int i = 1; i < n; ++i) {
        ++l[i - p[i] + 1]; --l[i + 1];
        ++r[i]; --r[i + p[i]];
    }

    for (int i = 1; i < n; ++i) {
        (ans += p[i] >> 1) %= mod;
        (l[i] += l[i - 1]) %= mod; (r[i] += r[i - 1]) %= mod;
        if (s[i] != -3)
            left[i - 1 >> 1] = l[i], right[i - 1 >> 1] = r[i];
    }

    for (int i = tmp - 2; i >= 0; --i) (left[i] += left[i + 1]) %= mod;
    ans = ans * fix(ans - 1) % mod * inv2 % mod;

    for (int i = 0; i < tmp; ++i)
        ans = fix(ans - 1ll * right[i] * left[i + 1] % mod);
    printf("%lld\n", ans);
    return 0;
}