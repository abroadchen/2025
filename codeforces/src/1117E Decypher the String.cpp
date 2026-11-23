//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
第 1 次询问——取 26^2位（百位）
按每 26^2=676 个位置进一位：前 676 位给 'a'，再 676 位给 'b'，……每 676 位升一级。相当于把位置编号的百位（
26^2位）‍用字符编码。
返回值 (str[i]-'a') 就是该位置的实际百位值，乘上 26^2累入 bl[i]
第 2 次询问——取26 位（十位）
每 26 个位置进一位（模 26 循环）：把编号的十位（26 位）‍用字符编码。
(str[i]-'a') 为该位实际十位值 ×26 累入
第 3 次询问——取 1 位（个位）
每 1 位进一位（即每位置依次 'a','b',...循环）：把编号个位用字符编码。
(str[i]-'a') 为该位实际个位值，直接累入
累完三位后 bl[i] = 26²·百位 + 26·十位 + 个位 = 真实原字符编号。
ans[bl[i]] = res[i]：把第 i 个字符放回它在原串里编号为 bl[i] 的位置。
最终输出 !  加还原结果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 1e4+5, I = 26;

string res, s, str;
int bl[N];
char ans[N];
int main() {
    fast;
    cin >> res; int sz = res.size();
    s = "? ";
    char ch = 'a';
    rep(i,sz) {
        s += ch;
        if ((i+1)%(I*I) == 0) ch++;
    }
    cout << s << endl;
    cin >> str;
    rep(i,sz) bl[i] += (str[i]-'a')*I*I;
    ch = 'a'; s = "? ";
    rep(i,sz) {
        s += ch;
        if ((i+1)%I == 0) ch++;
        if (ch == 'z' + 1) ch = 'a';
    }
    cout << s << endl;
    cin >> str;
    rep(i,sz) bl[i] += (str[i]-'a')*I;
    ch = 'a'; s = "? ";
    rep(i,sz) {
        s += ch; ch++;
        if (ch == 'z' + 1) ch = 'a';
    }
    cout << s << endl;
    cin >> str;
    rep(i,sz) bl[i] += str[i] - 'a';
    rep(i,sz) ans[bl[i]] = res[i];
    cout << "! " << ans;
    return 0;
}