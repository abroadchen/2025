//
// Created by Psy.C on 2025/11/9.
//

#include <cstdio>
using namespace std;

int main() {
    int r, g, b; scanf("%d %d %d", &r, &g, &b);
    r = (r + 1) / 2; g = (g + 1) / 2; b = (b + 1) / 2;

    int ans(0);
    if (b >= g && b >= r) ans = 30 + 3 * b - 1;
    else if (g >= r) ans = 30 + 3 * g - 2;
    else ans = 30 + 3 * r - 3;
    printf("%d\n", ans);
    return 0;
}