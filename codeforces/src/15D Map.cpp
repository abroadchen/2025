//
// Created by Psy.C on 2025/9/16.
//

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cctype>
#define LL long long
using namespace std;

template<class T> inline T& RD(T& x) {
    char c;
    while (!isdigit(c=getchar()));
    x = c - '0';
    while (isdigit(c=getchar())) x = x * 10 + c - '0';
    return x;
}
LL Map[1010][1010], ans[1010][1010]={0}, Min[1010][1010];
int que[1010];
bool mark[1010][1010];

void cal_min(int n, int m, int a, int b) {
    int i, j, S, E;
    for (i = 1; i <= n; ++i) {
        S = 0, E = 0;
        for (j = m; j >= 1; --j) {
            while (E > S && Map[i][que[E - 1]] > Map[i][j]) E--;
            que[E++] = j;
            while (S < E && que[S] > j + b - 1) S++;
            Min[i][j] = Map[i][que[S]];
        }
    }
    for (j = 1; j <= m; ++j) {
        S = 0, E = 0;
        for (i = n; i >= 1; --i) {
            while (E > S && Min[que[E - 1]][j] > Min[i][j]) E--;
            que[E++] = i;
            while (S < E && que[S] > i + a - 1) S++;
            Map[i][j] = Min[que[S]][j];
        }
    }
}

struct N {
    int x, y; LL val;
    bool operator<(const N& o) const {
        if (val != o.val) return o.val < val;
        if (x != o.x) return o.x < x;
        return o.y < y;
    }
} tmp;

priority_queue<N> q;
int x[1000100], y[1000100];
LL val[1000100];
int main() {
    int i, j, n, m, a, b; RD(n); RD(m); RD(a); RD(b);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            RD(Map[i][j]);
    for (i = n; i >= 1; --i)
        for (j = m; j >= 1; --j)
            ans[i][j] = Map[i][j] + ans[i + 1][j] + ans[i][j + 1] - ans[i + 1][j + 1];

    int N = n - a + 1, M = m - b + 1;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            ans[i][j] = ans[i][j] - ans[i + a][j] - ans[i][j + b] + ans[i + a][j + b];

    cal_min(n, m, a, b);

    for (i = N; i >= 1; --i)
        for (j = M; j >= 1; --j)
            q.push({i, j, ans[i][j] - Map[i][j] * a * b});

    memset(mark, false, sizeof(mark));

    int L, R, T, B, Top = 0;
    while (q.empty() == false) {
        tmp = q.top(); q.pop();
        if (mark[tmp.x][tmp.y]) continue;
        T = max(1, tmp.x - a + 1), B = min(n, tmp.x + a - 1);
        L = max(1, tmp.y - b + 1), R = min(m, tmp.y + b - 1);

        for (i = T; i <= B; ++i)
            for (j = L; j <= R; ++j)
                mark[i][j] = true;
        x[Top] = tmp.x, y[Top] = tmp.y, val[Top] = tmp.val, Top++;
    }

    printf("%d\n", Top);
    for (i = 0; i < Top; ++i)
        printf("%d %d %I64d\n", x[i], y[i], val[i]);


    return 0;
}