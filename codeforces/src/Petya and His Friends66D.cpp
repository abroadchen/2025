//
// Created by Psy.C on 2025/10/30.
//
/*
 *puts()函数会自动在输出末尾添加换行符
 *
 *
 */
#include <cstdio>
using namespace std;

long n;

int main() {
    scanf("%ld", &n);
    if (n == 2) puts("-1");
    else printf("6\n10\n15\n");

    for (long i = 3; i < n; ++i) printf("%ld\n", i * 6);
    return 0;
}