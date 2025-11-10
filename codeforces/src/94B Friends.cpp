//
// Created by Psy.C on 2025/11/10.
//
//a-1 和 b-1 将节点编号转换为对应的数组索引
#include <cstdio>
using namespace std;

int main() {
    int n; scanf("%d",&n);
    bool f(1);
    if (n == 5) {
        f = 0;
        int arr[5] = {0};
        for (int i = 0, a, b; i < n; ++i) {
            scanf("%d %d", &a, &b);
            ++arr[a - 1]; ++arr[b - 1];
        }
        for (int i : arr) if (i != 2) { f = 1; break; }
    }
    if (f) puts("WIN");
    else puts("FAIL");
    return 0;
}