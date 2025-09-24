//
// Created by Psy.C on 2025/9/24.
//

#include <cmath>
#include <cstdio>
using namespace std;

int main() {

    long x, y; scanf("%ld %ld\n", &x, &y);
    double d = x * x + y * y;

    long ans = sqrt(d);
    if (ans * ans == d) puts("black");
    else {
        if (x * y < 0) ++ans;
        puts(ans % 2 ? "white" : "black");
    }
    return 0;
}