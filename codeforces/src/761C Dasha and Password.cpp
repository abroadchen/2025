//
// Created by Psy.C on 2026/9/5.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 55, inf = 0x3f3f3f3f;

int n, m, dp[N][2][2][2];
char s[N][N];

bool isdigit(char ch) {
    if (ch >= '0' && ch <= '9') return true;
    return false;
}
bool isletter(char ch) {
    if (ch >= 'a' && ch <= 'z') return true;
    return false;
}
bool issymbols(char ch) {
    if (ch == '*' || ch == '&' || ch == '#') return true;
    return false;
}

int solve(int pos, bool d, bool l, bool sb) {
    if (pos == n) {//遍历完所有行
        if (d && l && sb) return 0;//已经满足所有条件，代价为 0
        return inf;//条件不满足，返回无穷大
    }
    if (dp[pos][d][l][sb] != -1) return dp[pos][d][l][sb];
    int ans = inf;
    for (int j = 0; j < m; ++j) {//枚举当前行的每一列
        int mn = min(j, m-j);//移动代价：可以向左走j步或向右走(m-j)步，取较小值
        //根据字符类型更新状态并递归
        if (isdigit(s[pos][j]))
            ans = min(ans, mn+solve(pos+1, 1, l, sb));
        else if (isletter(s[pos][j]))
            ans = min(ans, mn+solve(pos+1, d, 1, sb));
        else if (issymbols(s[pos][j]))
            ans = min(ans, mn+solve(pos+1, d, l, 1));
    }
    return dp[pos][d][l][sb] = ans;
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0, 0, 0) << '\n';//从第0行开始，三个标记均未出现
    return 0;
}