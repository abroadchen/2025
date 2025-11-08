//
// Created by Psy.C on 2025/9/25.
//

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {

    int n, m, x, y; scanf("%d%d%d%d", &n, &x, &m, &y);

    int l  = abs(y - x);
    long long ans = n + m + 1;

    for (int i = 1; i <= n; ++i) {
        if (abs(l - i) < m)
            ans += 2 * min(m, i + l - 1) +
                ((l - i) * 2 ^ -int(l >= i));//将布尔表达式转换为整数(-1或0)
    }

    printf("%lld\n", ans);
    return 0;
}