//
// Created by Psy.C on 2025/11/6.
//
/*
 *N-1
 *可以避免访问primes[15]导致的越界问题
 */
#include <cstdio>
using namespace std;

const int N = 15, primes[] = {
    2, 3, 5, 7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47
};
int n, m;
bool ans(0);

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < N - 1; ++i) {//如果找到这样的相邻质数对
        if (n == primes[i] && m == primes[i + 1]) ans = 1;
    }
    ans ? printf("YES\n") : printf("NO\n");
    return 0;
}