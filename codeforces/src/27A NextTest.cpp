//
// Created by Psy.C on 2025/9/20.
//

#include <cstdio>
using namespace std;

int main() {

    const int maxn = 3002;
    bool tests[maxn] = {0};

    int n(0); scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int temp; scanf("%d", &temp);
        tests[temp] = 1;
    }

    for (int i = 1; i < maxn; ++i) {
        if (!tests[i]) {
            printf("%d\n", i);
            break;
        }
    }
    
    return 0;
}