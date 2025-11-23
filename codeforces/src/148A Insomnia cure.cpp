//
// Created by Psy.C on 2025/11/21.
//时间复杂度：O(d) 空间复杂度：O(1)
/*
 *
*int solve(int k, int l, int m, int n, int d) {
    return d/k + d/l + d/m + d/n
         - d/lcm(k,l) - d/lcm(k,m) - d/lcm(k,n)
         - d/lcm(l,m) - d/lcm(l,n) - d/lcm(m,n)
         + d/lcm(k,l,m) + d/lcm(k,l,n) + d/lcm(k,m,n) + d/lcm(l,m,n)
         - d/lcm(k,l,m,n);
}
 */
#include <cstdio>
using namespace std;

int main() {
    int k, l, m, n; scanf("%d\n%d\n%d\n%d\n", &k, &l, &m, &n);
    int d; scanf("%d\n", &d);
    int res = 0;
    for (int i = 1; i <= d; ++i) {
        if (i % k == 0 || i % l == 0 || i % m == 0 || i % n == 0)
            ++res;
    }
    printf("%d\n", res);
    return 0;
}