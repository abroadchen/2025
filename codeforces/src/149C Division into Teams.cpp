//
// Created by Psy.C on 2025/11/22.
//

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;

int main() {
    int n; scanf("%d\n",&n);
    vector<ii> v(n);
    for (int i = 0, s; i < n; ++i) {
        scanf("%d",&s);
        v[i] = {s,i+1};//{元素值, 原始位置(1-indexed)}
    }
    sort(v.begin(), v.end());
    printf("%d\n", (n + 1) / 2);//输出第一组的元素个数（向上取整）
    for (int i = 0; i < n; i += 2) printf("%d ", v[i].second);
    printf("\n%d\n", n / 2);
    for (int i = 1; i < n; i += 2) printf("%d ", v[i].second);
    puts("");
    return 0;
}