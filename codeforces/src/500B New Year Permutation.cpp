//
// Created by Psy.C on 2026/2/23.
//

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 301;
int fa[N];
inline int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, p[N];
char s[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &p[i]), fa[i] = i;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s+1);
        for (int j = 1; j <= n; ++j)
            if (s[j] == '1') {//节点i和节点j之间有边
                if (int x = find(i), y = find(j); x != y)//两个节点连通但不属于同一集合
                    fa[y] = x;
            }
    }
    for (int i = 1; i <= n; ++i) {
        int k = i;
        for (int j = i + 1; j <= n; ++j)
            if (find(i) == find(j) && p[j] < p[k])//与节点i属于同一连通分量的所有节点中寻找值最小的节点
                k = j;
        swap(p[k], p[i]);//交换到位置i
        printf("%d ", p[i]);
    }
    return 0;
}