//
// Created by Psy.C on 2025/11/19.
//
/*
*i：字符串位置（0到n-1）
j：某种计数（0到m）
k：状态标识（0或1）
 *
*如果当前字符不是'F'，则计数j增加1
根据状态k决定是+1还是-1
*如果当前字符不是'T'，则计数j增加1
状态k翻转
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define maxx(x,y) if (y>x) x=y
using namespace std;

const int N = 105;
char s[N];
int m, n, f[N][55][2], ans;

int main() {
    scanf("%s%d", s, &m); n = strlen(s);
    memset(f, 200, sizeof(f));
    f[0][0][0] = f[0][0][1] = 0;
    rep(i,n) rep(j,m+1) rep(k,2) {
        maxx(f[i+1][j+(s[i]!='F')][k], f[i][j][k] + (k?1:-1));
        maxx(f[i+1][j+(s[i]!='T')][!k], f[i][j][k]);
    }
    for (int i = m; i >= 0; i -= 2) {
        maxx(ans, f[n][i][0]);
        maxx(ans, f[n][i][1]);
    }
    printf("%d\n", ans);
    return 0;
}