//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
dg：度数（因为用 1 基索引的 rep）。
s：节点颜色串。后面 s = ' ' + s 使其从下标 1 开始。
vc：邻接表，用于枚举一个节点的所有邻居
情况 1：小 n 特判
n<=2：直接判定平局。
n==3：数一数 'W' 的数量，若 ≥2 则白方胜，否则平局。
情况 2：大度点直接判 White 只要存在度数 ≥4 的节点，直接判 White 胜。
情况 3：度数为 3 的节点（T 形分支）
对每个度数为 3 的节点 i，取其三个邻居 a、b、c。
统计这三个邻居中度数 >1（即非叶子的分支）的数量 ck。
若 ck>=2（即这个 T 形点至少有两条不是"死路"的分支），判 White。
情况 4：ct = 度数为 3 的节点个数，继续分
子情况 4.1：ct == 2（两个三叉点）
若存在任意 'W' 点 → White 胜。
否则返回 n&1（n 为奇数返回 1，偶数返回 0）
子情况 4.2：ct == 1（一个三叉点）
n==4 特判：找出唯一三叉点 x，其余节点若有 'W' 则 White。
对于一般 n==4 以外：找一个"叶子其一端邻居是三叉点"的叶子 x。若除 x 外有 'W' → White；若 x 是 'N' → Draw；否则返回 !(n&1)（n 为偶数则 1，奇数则 0）
子情况 4.3：ct == 0（没有三叉点，纯链状）
所有非叶子节点（度 ≥2）中，只要出现 'W' 直接判 White。
否则 f 表示 "n 奇数 && 所有叶子都是 'W'"。返回 f。
读 n，重置度数/邻接表。
读 n-1 条边，更新度数并建邻接表。
读颜色串，并在前面拼一个空格使其 1 基索引（s = ' ' + s）。
调用 check()，结果作为 str 下标输出 "Draw\n" 或 "White\n"。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1; i<=n; i++)
using namespace std;

constexpr int N = 5e5+5;

int n, dg[N];
string s;
vector<int> vc[N];
int check() {
    if (n <= 2) return 0;
    if (n == 3) {
        int ct = 0;
        rep(i,n) ct += s[i] == 'W';
        if (ct >= 2) return 1;
        return 0;
    }
    rep(i,n) if (dg[i] >= 4) return 1;
    rep(i,n) {
        if (dg[i]^3) continue;
        int a = vc[i][0], b = vc[i][1], c = vc[i][2];
        int ck = (dg[a]>1)+(dg[b]>1)+(dg[c]>1);
        if (ck >= 2) return 1;
    }
    int ct = 0;
    rep(i,n) ct += dg[i] == 3;
    if (ct == 2) {
        rep(i,n) if (s[i] == 'W') return 1;
        return n&1;
    }
    if (ct == 1) {
        if (n == 4) {
            int x = 0, cnt = 0;
            rep(i,n) if (dg[i] == 3) x = i; else cnt += s[i] == 'W';
            if (s[x] == 'W') return 1;
            return cnt > 0;
        }
        int x = 0;
        rep(i,n) {
            if (dg[i]^1) continue;
            if (dg[vc[i][0]]^3) { x = i; break; }
        }
        rep(i,n) if ((i^x) && s[i] == 'W') return 1;
        if (s[x] == 'N') return 0;
        return !(n&1);
    }
    if (ct == 0) {
        bool f = n&1;
        rep(i,n) {
            if (dg[i] == 1) f &= s[i] == 'W';
            else if (s[i] == 'W') return 1;
        }
        return f;
    }
}

string str[] = {"Draw\n","White\n"};
void solve() {
    cin >> n;
    rep(i,n) dg[i] = 0;
    rep(i,n) vc[i].clear();
    for (int i = 2, x, y; i <= n; i++) {
        cin >> x >> y; dg[x]++, dg[y]++;
        vc[x].push_back(y); vc[y].push_back(x);
    }
    cin >> s; s = ' ' + s;
    cout << str[check()];
}

int main() {
    fast;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}