//
// Created by Psy.C on 2025/11/5.
//

#include <cstdio>
using namespace std;

int main() {

    int t, n, m, k; scanf("%d", &t);
    for (int i = 1; i <= t; ++i) {
        scanf("%d%d%d", &n, &m, &k);
        double res = 1.0 / (1.0 / (n - m) + 1.0 * k * k * (n - m) / n / m);
        printf("%.10lf\n", res);
    }
    return 0;
}