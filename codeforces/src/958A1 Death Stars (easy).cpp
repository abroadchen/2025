//
// Created by Psy.C on 2026/10/20.
//
/**
恒等：(i,j) → (i,j)
上下翻转（关于水平中线）：(i,j) → (n-i+1, j)
左右翻转（关于垂直中线）：(i,j) → (i, n-j+1)
旋转 180°（上下+左右）：(i,j) → (n-i+1, n-j+1)
转置（主对角线翻转）：(i,j) → (j,i)
另一斜对角镜像：(i,j) → (n-j+1, i)
转置+另一正交（次对角线翻转）：(i,j) → (j, n-i+1)
旋转 90°：(i,j) → (n-j+1, n-i+1)
 */
#include <bits/stdc++.h>
#define rep(i,j) for(int i=1; i <= j; i++)
using namespace std;

constexpr int N = 12;

int n, flg;
char a[N][N], b[N][N];
int main() {
    scanf("%d", &n);
    rep(i,n) scanf("%s", a[i]+1);
    rep(i,n) scanf("%s", b[i]+1);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[i][j]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[n-i+1][j]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[i][n-j+1]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[n-i+1][n-j+1]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[j][i]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[n-j+1][i]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[j][n-i+1]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    flg = 1;
    rep(i,n) rep(j,n) if (a[i][j] != b[n-j+1][n-i+1]) flg = 0;
    if (flg) puts("Yes"), exit(0);
    puts("No");
    return 0;
}

/**

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 12;
int n;
char a[N][N], b[N][N];

// 变换描述: (rev0: i 是否反向; rev1: j 是否反向; swp: 是否交换 i,j)
// 映射: (i,j) -> (ni, nj)
auto trans = [](int i, int j, int rev0, int rev1, int swp) {
    int x = swp ? j : i;
    int y = swp ? i : j;
    if (rev0) x = n - x + 1;
    if (rev1) y = n - y + 1;
    return make_pair(x, y);
};

bool check(int rev0, int rev1, int swp) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            auto [ni, nj] = trans(i, j, rev0, rev1, swp);
            if (a[i][j] != b[ni][nj]) return false;
        }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%s", a[i]+1);
    for (int i = 1; i <= n; i++) scanf("%s", b[i]+1);

    for (int rev0 = 0; rev0 <= 1; rev0++)
        for (int rev1 = 0; rev1 <= 1; rev1++)
            for (int swp = 0; swp <= 1; swp++)
                if (check(rev0, rev1, swp)) { puts("Yes"); return 0; }
    puts("No");
    return 0;
}



#include <bits/stdc++.h>
using namespace std;
constexpr int N = 12;
int n;
char a[N][N], b[N][N];

// 比较: a 经过变换 f 得到的结果是否等于 b
// f(i,j) 返回 (ni, nj)，即 a 中 (i,j) 在 b 中的对应坐标
bool cmp(const function<pair<int,int>(int,int)>& f) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            auto [ni, nj] = f(i, j);
            if (a[i][j] != b[ni][nj]) return false;
        }
    return true;
}

bool symmetric() {
    // 8 种对称变换
    return cmp([](int i, int j){ return make_pair(i,      j     ); })   // 恒等
        || cmp([](int i, int j){ return make_pair(n-i+1,  j     ); })   // 上下翻转
        || cmp([](int i, int j){ return make_pair(i,      n-j+1); })    // 左右翻转
        || cmp([](int i, int j){ return make_pair(n-i+1,  n-j+1); })    // 旋转180
        || cmp([](int i, int j){ return make_pair(j,      i     ); })   // 转置
        || cmp([](int i, int j){ return make_pair(n-j+1,  i     ); })
        || cmp([](int i, int j){ return make_pair(j,      n-i+1); })    // 次对角镜像
        || cmp([](int i, int j){ return make_pair(n-j+1,  n-i+1); });   // 旋转90
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%s", a[i]+1);
    for (int i = 1; i <= n; i++) scanf("%s", b[i]+1);
    puts(symmetric() ? "Yes" : "No");
    return 0;
}

 */
