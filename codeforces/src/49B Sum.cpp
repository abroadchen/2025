//
// Created by Psy.C on 2025/10/13.
//
/*
*使用模10运算提取每一位数字
检查是否有任何数字大于等于进制r
如果有任何数字≥r，则该数字不能在该进制中表示
无效返回false，有效返回true
 *
*第一个循环：将数字a从其数字表示转换为进制r中的实际值
第二个循环：转换数字b并将其加到总和中
第三个循环：计算总和在进制r中有多少位数字
返回数字计数（长度）
 *
 */
#include <cstdio>
using namespace std;

const long N = 1000;
long a, b, maxL(0);

bool check(long a, long b, long r) {
    while (a > 0) {
        if (a % 10 >= r) return false;
        a /= 10;
    }
    while (b > 0) {
        if (b % 10 >= r) return false;
        b /= 10;
    }
    return true;
}

long getL(long a, long b, long r) {
    long sum(0), mult(1), len(0);
    while (a > 0) {
        sum += mult * (a % 10);
        mult *= r;
        a /= 10;
    }
    mult = 1;
    while (b > 0) {
        sum += mult * (b % 10);
        mult *= r;
        b /= 10;
    }
    while (sum > 0) {
        sum /= r;
        ++len;
    }
    return len;
}


int main() {
    scanf("%ld %ld", &a, &b);
    for (long i = 2; i <= N; ++i) {
        if (!check(a, b, i)) continue;
        long l = getL(a, b, i);
        maxL = (maxL > l) ? maxL : l;
    }
    printf("%ld\n", maxL);
    return 0;
}