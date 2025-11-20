//
// Created by Psy.C on 2025/11/20.
//
/*
*贪心地选择特殊边构建生成树
tot: 已选择的特殊边数量
限制条件：tot * 2 + 1 ≤ n（特殊边数量不能超过(n-1)/2）
*重新初始化并查集
先加入已选的特殊边
继续选择未使用的特殊边，直到达到目标数量tot * 2 + 1 = n
 *添加普通边来完成整个生成树
 *
*检查是否达到目标特殊边数量
输出生成树的边数(n-1)和所选边的编号
 */
#include <algorithm>
#include <cstdio>
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int N = 1010, M = 1e5+20;
int n, m, fa[N], used[M];

struct edge {
    int a, b, w, id;
    edge(int x=0, int y=0, int ok=0, int z=0): a(x), b(y), w(ok), id(z) {}
    bool operator<(const edge& rhs) const { return w < rhs.w; }
} e[M];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    rep(i,n) fa[i] = i;
    if (n % 2 == 0) return printf("-1"), 0;
    if (n == 1 || n == 0) return printf("0"), 0;
    char s[5];
    rep(i,m) {
        int a, b; scanf("%d%d%s", &a, &b, s);
        if (s[0] == 'S') e[i] = {a, b, 1, i};
        else e[i] = {a, b, 0, i};
    }
    sort(e + 1, e + m + 1);
    int tot = 0;
    rep(i,m) {
        int a = e[i].a, b = e[i].b;
        if (unite(a, b) && e[i].w == 1) { tot++; used[e[i].id] = 1; }
    }
    if (tot * 2 + 1 > n) return printf("-1"), 0;
    rep(i,n) fa[i] = i;
    rep(i,m) if (used[e[i].id]) unite(e[i].a, e[i].b);
    rep(i,m) {
        if (e[i].w == 1 && !used[e[i].id]) {
            if (unite(e[i].a, e[i].b)) { tot++; used[e[i].id] = 1; }
        }
        if (tot * 2 + 1 == n) break;
    }
    rep(i,m) {
        if (!used[e[i].id] && e[i].w == 0) {
            if (unite(e[i].a, e[i].b)) used[e[i].id] = 1;
        }
    }
    if (tot * 2 + 1 < n) return printf("-1"), 0;
    printf("%d\n", n - 1);
    rep(i,m) if (used[i]) printf("%d ", i);
    return 0;
}