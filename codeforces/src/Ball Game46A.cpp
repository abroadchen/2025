//
// Created by Psy.C on 2025/9/30.
//

#include <cstdio>
using namespace std;

int main() {

    int n; scanf("%d",&n);
    int cur(0);
    for (int i = 1; i < n; ++i) {
        cur += i;
        cur %= n;//保留cur除以n的余数，防止数值过大
        printf("%d ",cur + 1);
    }
    printf("\n");
    return 0;
}