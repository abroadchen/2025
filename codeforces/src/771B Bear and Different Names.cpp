//
// Created by Psy.C on 2026/9/8.
//
/**
ans[55][3]：存 n 个名字，每个名字由两个字符组成（如 Aa、Ab…）。
读入 n（名字个数）、k（窗口大小）。
c1、c2：用来生成新名字的两个字符游标，从 Aa 开始，依次 Ab,Ac,...,Az,Ba,Bb,...（c2 超过 'z' 时 c1 推进到 'B' 并重置 c2='a'）
有 n-k+1 个询问（对应 n 个名字中所有长度为 k 的连续窗口）。
每次读入一个字符串 s，它为 "YES" 表示该窗口内 k 个名字互不相同，为 "NO" 表示窗口内存在重复（即至少有两个名字相同
对第一个窗口 [0, k-1]：
若 s=="YES"：窗口内 k 个名字全互不相同 → 直接把 ans[0..k-1] 逐个赋新名字（互不相同）。
若 s=="NO"：窗口内必须有重复。技巧是让首尾两个名字相同（ans[0] 和 ans[k-1] 赋同一个名字），中间 ans[1..k-2] 各赋不同新名字——这样保证窗口内存在重复（首尾重复）且其余各不同
对第 i 个窗口 [i, i+k-1]，此时前面 ans[i..i+k-2] 已经确定（即窗口内前 k-1 个名字已知），只需决定新加入的最后一个 ans[i+k-1]：
若 s=="YES"：窗口内 k 个必须全不同，而前 k-1 个互不相同，所以新加的这个名字必须与它们都不同 → 赋一个全新名字。
若 s=="NO"：窗口内必须有重复。最简单做法是让新加入的名字和窗口第一个 ans[i] 相同（ans[i+k-1]=ans[i]），这样保证窗口内有重复，同时不影响前面已确定的条件
依次输出这 n 个名字（每名字两个字符，用空格隔开）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char ans[55][3];
int main() {
    fast;
    int n, k; cin >> n >> k;
    char c1 = 'A', c2 = 'a';
    for (int i = 0; i < n-k+1; ++i) {
        string s; cin >> s;
        if (i == 0) {
            if (s == "YES") {
                for (int j = i; j < i+k; ++j) {
                    ans[j][0] = c1; ans[j][1] = c2++;
                    if (c2 > 'z') c1 = 'B', c2 = 'a';
                }
            } else {
                ans[i][0] = ans[i+k-1][0] = c1;
                ans[i][1] = ans[i+k-1][1] = c2++;
                for (int j = i+1; j < i+k-1; ++j) {
                    ans[j][0] = c1; ans[j][1] = c2++;
                    if (c2 > 'z') c1 = 'B', c2 = 'a';
                }
            }
        } else {
            if (s == "YES") {
                ans[i+k-1][0] = c1; ans[i+k-1][1] = c2++;
            } else {
                ans[i+k-1][0] = ans[i][0]; ans[i+k-1][1] = ans[i][1];
            }
            if (c2 > 'z') c1 = 'B', c2 = 'a';
        }
    }
    for (int i = 0; i < n; ++i) cout << ans[i][0] << ans[i][1] << ' ';
    cout << '\n';
    return 0;
}