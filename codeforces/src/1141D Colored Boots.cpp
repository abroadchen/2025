//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
遍历第一串的 n 个字符
c=='?'	是通配符
q1[++q1[0]] = i	q1[0] 自增后作为下标，把位置 i 存进去（q1[0] 同时充当计数器）
p1[c-'a'+1][++p1[...][0]] = i	把字符转成 1..26 的编号，p1[x][0] 自增作为下标，存位置 i
逻辑与第一串完全相同，只是存到 q2 / p2
min(p1[i][0], p2[i][0])	字母 i 在第一、二串里的个数取较小者，就是能配成的对数
ans += ...	累加进答案
p1[i][0] > p2[i][0]	第一串该字母更多
r1 += p1[i][0]-p2[i][0]	r1 累加第一串多出来的、该字母剩余没有配对的个数
否则	r2 += p2[i][0]-p1[i][0]，r2 累加第二串多出来的剩余个数
min(q1[0], r2)	第一串的 ?（q1 个数）配第二串多出来的字母（r2 个）→
取两者较小值
| min(q2[0], r1) | 第二串的 ? 配第一串多出来的字母（r1 个）|
| 两者相加进 ans | ? 万能匹配让多余字母也能配 |
qa = max(q1[0]-r2, 0)	第一串的 ? 用掉 r2 个（配第二串多出的字母）后还剩余的 ? 数（不能为负）
qb = max(q2[0]-r1, 0)	第二串剩余 ? 数
min(qa,qb)	剩余 ? 两两配对，取较小者加进答案

cout << ans	先输出总数
rep(j, min(p1[i][0], p2[i][0]))	对每个字母，配台数 = 两串该字母较少的个数
p1[i][j] << ' ' << p2[i][j]	依次输出"第一串位置 + 第二串位置"作为一对
if (p1[i][0]==p2[i][0]) continue	两串该字母个数相等，无多余可配
p1[i][0] > p2[i][0]	第一串字母 i 多
rep(j, p1[i][0]-p2[i][0])	遍历多出来的那些（第 p2+1 个到第 p1 个位置）
++c2 > q2[0]	第二串 ? 用完（c2 是 ? 的序号游标）则 break
输出：第一串多出的字母位置 + 第二串 ? 位置	配成一对
else 分支	对称处理：第二串多出时，用第一串的 ? 去配
c1, c2 分别是第一串、第二串 ? 数组的读取游标，q1[0], q2[0] 是 ? 总数
++c2 <= q2[0] && ++c1 <= q1[0]	两边 ? 都还有剩余才继续
q1[c1] << ' ' << q2[c2]	第一串 ? 与第二串 ? 配对输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 15e4+5, M = 26;

int n, q1[N], q2[N], p1[M+1][N], p2[M+1][N], ans, r1, r2, c1, c2;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        char c; cin >> c;
        if (c == '?') q1[++q1[0]] = i;
        else p1[c-'a'+1][++p1[c-'a'+1][0]] = i;
    }
    rep(i,n) {
        char c; cin >> c;
        if (c == '?') q2[++q2[0]] = i;
        else p2[c-'a'+1][++p2[c-'a'+1][0]] = i;
    }
    rep(i,M) {
        ans += min(p1[i][0],p2[i][0]);
        p1[i][0] > p2[i][0] ? r1 += p1[i][0]-p2[i][0] : r2 += p2[i][0]-p1[i][0];
    }
    ans += min(q1[0],r2) + min(q2[0],r1);
    int qa = max(q1[0]-r2,0), qb = max(q2[0]-r1,0);
    ans += min(qa,qb);
    cout << ans << '\n';
    rep(i,M) rep(j,min(p1[i][0],p2[i][0]))
        cout << p1[i][j] << ' ' << p2[i][j] << '\n';
    rep(i,M) {
        if (p1[i][0] == p2[i][0]) continue;
        if (p1[i][0] > p2[i][0]) {
            rep(j,p1[i][0]-p2[i][0]) {
                if (++c2 > q2[0]) break;
                cout << p1[i][p2[i][0] + j] << ' ' << q2[c2] << '\n';
            }
        } else {
            rep(j,p2[i][0]-p1[i][0]) {
                if (++c1 > q1[0]) break;
                cout << q1[c1] << ' ' << p2[i][p1[i][0]+j] << '\n';
            }
        }
    }
    while (++c2 <= q2[0] && ++c1 <= q1[0])
        cout << q1[c1] << ' ' << q2[c2] << '\n';
    return 0;
}