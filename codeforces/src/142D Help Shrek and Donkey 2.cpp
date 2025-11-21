//
// Created by Psy.C on 2025/11/21.
//

#include <cstdio>
using namespace std;

const int N = 107, M = 13;
int n, m, k,
vv, vt, t, vf, vs, f(0), ans[M];
char ch[N];

int main() {
    scanf(" %d %d %d", &n, &m, &k); ++k;
    for (int i = 0; i < n; ++i) {
        scanf(" %s", ch); vv = vt = t = 0;
        for (int j = 0; j < m; ++j) {
            if (ch[j] == '-') if (t) ++vv;
            if (ch[j] == 'G') ++t, ++vt;
            if (ch[j] == 'R') --t, ++vt;
        }
        if (t) {
            if (vt == m) continue;
            if (t > 0) ++vf;
            else ++vs;
        } else {
            f = 1;
            if (vv) ++vf, ++vs;
            for (int u = 0, v = 1; vv; ++u, v<<=1) {
                if (vv & v) { vv ^= v; ans[i] = (ans[i]+1)%k; }
            }
        }
    }
    if (!vf) printf("Second\n");
    else if (!vs) printf("First\n");
    else if (!f) printf("Draw\n");
    else {
        f = 0;
        for (int i = 0; i < M; ++i) if (ans[i]) { f = 1; break; }
        printf("%s\n", f ? "First" : "Second");
    }
    return 0;
}