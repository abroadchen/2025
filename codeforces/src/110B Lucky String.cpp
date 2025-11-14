//
// Created by Psy.C on 2025/11/14.
//

#include <cstdio>
using namespace std;

int main() {

    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        if (i % 4 == 0) printf("a");
        else if (i % 4 == 1) printf("b");
        else if (i % 4 == 2) printf("c");
        else if (i % 4 == 3) printf("d");
    }
    printf("\n");
    return 0;
}