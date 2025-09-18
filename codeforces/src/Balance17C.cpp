//
// Created by Psy.C on 2025/9/17.
//
/*
n: 字符串长度
m: 计算得出的辅助变量
s: 输入字符串
ne[i][j]: 从位置i开始下一个字符j的位置
f[i][a][b][c]: 动态规划状态，表示到位置i时各字符出现次数的状态
 *
 *
*从后往前计算ne数组：
对每个位置i，先继承下一个位置的ne值
如果i>0，则更新当前位置字符的ne值为i
 *
*四重循环进行状态转移：
枚举当前位置i和各字符计数状态(a,b,c)
枚举下一个要添加的字符j(0,1,2对应a,b,c)
如果存在这样的字符(即ne[i][j]不为-1)
更新对应的状态：到位置t时各字符计数增加的状态
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <string>
#include <cstring>
#define sz(a) (int)a.size()
#define rep(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;

const int N = 155, P = 51123987;

int n, m;
string s;
int ne[N][3], f[N][55][55][55];

void add(int& a, int b) {
    if ((a += b) >= P)
        a -= P;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> s;
    s = " " + s;//在字符串前添加空格，使下标从1开始
    memset(ne, -1, sizeof(ne));
    for (int i = sz(s)-1; ~i; --i) {
        rep (j, 0, 3) ne[i][j] = ne[i+1][j];
        if (i) ne[i][s[i]-'a'] = i;
    }
    m = (n + 2) / 3;
    f[0][0][0][0] = 1;

    rep (i, 0, n + 1) {
        rep (a, 0 , m + 1) rep (b, 0, m + 1) rep (c, 0, m + 1) {
            rep (j, 0, 3) if (~ne[i][j]) {
                int t = ne[i][j];
                add(f[t][a + (j == 0)][b + (j == 1)][c + (j == 2)], f[i][a][b][c]);
            }
        }
    }

    int ans = 0, l = n / 3, r = m;
    rep (i, 1, n + 1) {
        rep (a, l, r + 1) rep (b, l, r + 1) rep (c, l, r + 1) if (a + b + c == n) {
            add(ans, f[i][a][b][c]);
        }
    }
    cout << ans << endl;
    return 0;
}