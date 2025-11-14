//
// Created by Psy.C on 2025/11/14.
//

#include <cstdio>
using namespace std;

int main() {
    int n, x, y; scanf("%d %d %d",&n,&x, &y);
    int t = n / 2;
    if ((x == t || x == t + 1) && (y == t || y == t + 1)) puts("NO");
    else puts("YES");
    return 0;
}