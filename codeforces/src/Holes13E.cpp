//
// Created by Psy.C on 2025/9/15.
//

#include <cmath>
#include <cstdio>
#define maxn 1000010
using namespace std;

typedef long long ll;

int n, m, block, power[maxn], nxt[maxn], cnt[maxn], end[maxn];

inline ll read() {
    int x = 0, f = 1;
    int ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}



void update(int i, int j) {
    if (j > n) {
        nxt[i] = n + 1;
        cnt[i] = 1;
        end[i] = i;
    } else {
        if (i / block == j / block) {
            cnt[i] = cnt[j] + 1;
            end[i] = end[j];
            nxt[i] = nxt[j];
        } else {
            nxt[i] = j;
            end[i] = i;
            cnt[i] = 1;
        }
    }
}

void solve(int x) {
    int c = cnt[x], e = end[x];
    while (1) {
        x = nxt[x];
        if (x > n) break;
        c += cnt[x];
        e = end[x];
    }
    printf("%d %d\n", e, c);
}

int main() {

    n = (int)read(), m = (int)read();
    block = (int)ceil(sqrt(n * 1.0));
    for (int i = 1; i <= n; ++i) power[i] = (int)read();
    for (int i = n; i >= 1; --i) update(i, i + power[i]);

    for (int i = 0; i < m; ++i) {
        int q = (int)read();
        if (q) {
            int v = (int)read();
            solve(v);
        } else {
            int a = (int)read(), b = (int)read();
            update(a, a + b);
            for (int i = a - 1; i >= a / block * block; --i)
                update(i, i + power[i]);
            power[a] = b;
        }
    }
    return 0;
}