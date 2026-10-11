//
// Created by Psy.C on 2026/10/11.
//
/**
读入 11 行字符串（第 0-10 行）。注意这里存的是原始棋盘行的序号。
输入落子位置 (x, y)（1-based），减一后 x--, y-- 转成 0-based，再 %3 得到所在小区块的坐标（0-2）
m = x*3 + x 中的 x 其实是在为"中间夹一个分隔行"加偏移：第 x 个区块的真实起始行 = x*3 + x（前面的区块各占 3 行 + 1 个分隔行）。

列同理：n = y*3 + y = 4y，y=0→0-2、y=1→4-6、y=2→8-10
在目标区块（m..m+2 行，n..n+2 列）内，把所有 .（空格）改成 !（玩家标记）。
只要有一个空格被填，就把 flg 置 1
如果目标区块已经全部被占满（没有任何 .），即 flg==0，那么按照规则，对手可以在任意区块落子，所以代码把整个棋盘上所有 . 都填成 !
把 11 行（含可能的空格/分隔行）原样输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

string s[11];
int main() {
    fast;
    rep(i,0,10) getline(cin, s[i]);
    int x, y; cin >> x >> y; x--, y--; x%=3, y%=3;
    int m = x*3+x, n = y*3+y, flg = 0;
    rep(i,m,m+2) rep(j,n,n+2) {
        if (s[i][j] == '.') {
            s[i][j] = '!'; flg = 1;
        }
    }
    if (!flg) {
        rep(i,0,10) rep(j,0,10) {
            if (s[i][j] == '.')
                s[i][j] = '!';
        }
    }
    rep(i,0,10) cout << s[i] << '\n';
    return 0;
}