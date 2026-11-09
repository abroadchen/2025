//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
N=305：矩阵最大行列（可存到 305）。
M=4e5+5：操作序列上限（4 个字段×最多 4e5 条）。
cnt[N][N]：统计表——记录某格子作为"载体"被翻转的次数（用于第二遍后处理）。
ans[M][4]：答案操作数组，每一行存一次操作的 4 个坐标。
tot：当前已生成的操作总数。
口诀：cnt 管统计，ans 管输出，tot 管计数
每次记录一条操作 (x1,y1) → (x2,y2) 存入 ans。
同时 cnt[x2][y2]++ 记录在目标格子 (x2,y2) 上做了一次翻转——cnt 是给后处理用的。
f = s[k]=='1'：1 和 0 走不同的载体行——'1' 用第 1 行作载体，'0' 用第 2 行作载体（这就是为什么只有第 1、2 行被特殊处理）。
如果 (x,y) 本身已经在载体行（x==1 或 x==2）上，就不能自己翻转自己，得把载体换成另一个位置（用三元 y==1?2:1 在 y=1 与 y=2 之间切换），保证"载体"不是操作对象本身。
一句话：每一位 0/1 都对应一条、仅一条操作
读入初始矩阵的 n×m 个二进制串，每个串的每位字符都通过 add 生成一条操作。
per(k, ...) 从高位往低位遍历
只针对第 1、2 行、且列 j≥2 的格子：凡是 cnt[i][j] 非零（说明它被当作过载体多次），就补做 cnt[i][j] 次 ins(i,j,i,1)——把"载体翻转"与"实际目标翻转"抵消对应的次数补上，凑平引用计数。
t = tot：记住前半段一共多少条操作。
memset(cnt,0,...)：清空统计表，准备处理第二个矩阵
和第二遍逻辑完全对称，区别只在：

这次读入的是目标矩阵；
遍历方向变了：第一遍 per（高→低），第二遍 for（低→高）——方向相反，这正是为了让前后两段操作在"抵消"上形成对称的可撤销结构；
后处理同样补一次载体次数
先打印总操作数 tot。
前半段（第 1-t 条）：按 (x1,y1,x2,y2) 原序。
后半段（第 t+1-tot 条）：按 (x2,y2,x1,y1) 逆序（for 从 tot 倒到 t）——前后两段操作方向镜像对称，从而保证"先翻转后翻转同一组合返回原位"，实现净效果恰好把初始矩阵变成目标矩阵
*/
#include <bits/stdc++.h>
#define rep(i,n) for (i=1; i<=n; i++)
#define per(i,n) for (i=n; i>=0; i--)
using namespace std;

constexpr int N = 305, M = 4e5+5;

int cnt[N][N], ans[M][4], tot;
void ins(int x1, int y1, int x2, int y2) {
    cnt[x2][y2]++;
    ans[++tot][0] = x1; ans[tot][1] = y1; ans[tot][2] = x2; ans[tot][3] = y2;
}
void add(int x, int y, int f) {
    if (f) {
        if (x != 1) ins(x, y, 1, y);
        else ins(x, y, 1, y==1?2:1);
        return;
    }
    if (x != 2) ins(x, y, 2, y);
    else ins(x, y, 2, y==1?2:1);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, t;
string s;
int main() {
    int i, j, k;
    n = rd(), m = rd();
    rep(i,n) rep(j,m) {
        cin >> s;
        per(k,s.size()-1) add(i, j, s[k]=='1');
    }
    rep(i,2) for (j = 2; j <= m; j++) rep(k,cnt[i][j]) ins(i,j,i,1);
    t = tot; memset(cnt, 0, sizeof(cnt));
    rep(i,n) rep(j,m) {
        cin >> s;
        for (k = 0; k < s.size(); k++) add(i, j, s[k]=='1');
    }
    rep(i,2) for (j = 2; j <= m; j++) rep(k,cnt[i][j]) ins(i,j,i,1);
    cout << tot << '\n';
    rep(i,t) cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << ' ' << ans[i][3] << '\n';
    for (i = tot; i > t; i--) cout << ans[i][2] << ' ' << ans[i][3] << ' ' << ans[i][0] << ' ' << ans[i][1] << '\n';
    return 0;
}