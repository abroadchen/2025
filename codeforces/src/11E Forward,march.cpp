//
// Created by Psy.C on 2025/9/14.
//

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1e6+5;
const double eps = 1e-9;
char s[MAXN], cg[MAXN << 1];
int n, tot;
double f[MAXN << 1][2];

bool check(double avg) {
    f[0][0] = -avg, f[0][1] = 0;

    for (int i = 1; i <= tot; ++i) {
        f[i][0] = f[i - 1][1] + (cg[i] == 'L') - avg;
        f[i][1] = f[i - 1][0] + (cg[i] == 'R') - avg;
        f[i][0] = max(f[i][0], f[i][1] - avg);
        f[i][1] = max(f[i][1], f[i][0] - avg);
    }
    return f[tot][1] >= 0;
}




int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    if (s[1] == s[n] && s[1] == 'R') cg[++tot] = 'X';
    for (int i = 1; i <= n; ++i) {
        if (s[i] == s[i - 1] && s[i] != 'X') cg[++tot] = 'X';
        cg[++tot] = s[i];
    }
    if (s[1] == s[n] && s[1] == 'L') cg[++tot] = 'X';
    double l = 0, r = 100;
    while (fabs(l - r) > eps) {
        double mid = (l + r) / 2;
        if (check(mid / 100)) l = mid;
        else r = mid;
    }
    printf("%.6lf", (int)(r * 1e6) / (1e6));
    return 0;
}