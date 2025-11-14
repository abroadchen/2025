//
// Created by Psy.C on 2025/11/13.
//

#include <cstdio>
using namespace std;


void f4(int n) { for (int i = 0; i < n; ++i) printf("4"); }
void s7(int n) { for (int i = 0; i < n; ++i) printf("7"); }

int main() {
    int n, i; scanf("%d",&n);
    for (i = 0; i <= n/4; ++i) {
        int x = ((n - i*4)/7);//当使用i个4时，需要多少个7才能使总和等于n
        if ((i * 4 + x * 7) == n) {
            f4(i); s7(x);
            return 0;
        }
    }
    printf("-1");
    return 0;
}