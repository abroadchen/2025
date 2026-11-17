//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
mp[key]：记录某个引用 key 在正文中首次出现的顺序号（tot）。
node：存 { 顺序号idx, 完整bibitem行s }，operator< 按 idx 排序
从位置 f 起反复找 \cite{。
命中后 pos 是指\ 的位置，key 从 pos+6 开始（\cite{ 共 6 个字符），读到 } 为止得到 key。
mp[key] = ++tot：给这个 key 一个递增序号——即按正文出现先后排的序。
循环推进 f，能正常退出
碰到 \begin{thebibliography}{99}：置标志 f=1，跳过该行。
碰到 \end{thebibliography}：停止。
在 begin 之前的每一行 → 调用 find 提取引用并编号。
在 begin 之后的每一行 → 解析 \bibitem{key}（\bibitem{ 共 9 字符，偏移 9 得到 key），然后把 mp[key]（正文顺序号）和整行存入 v
若 v[i].idx 恰好等于 i+1（即现有 \bibitem 已按正文出现顺序排好）→ 输出 Correct。
否则输出 Incorrect，把 v 按 idx 升序排好，原样重输出 \bibitem 各行（带 \begin/\end 外壳）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

struct node {
    int idx; string s;
    bool operator<(const node &o) const { return idx < o.idx; }
};

map<string,int> mp;
int tot;
void find(const string &s) {
    int pos, f = 0;
    while ((pos = s.find("\\cite{", f)) != -1) {
        string res;
        for (f=pos+6; f < s.size() && s[f] != '}'; f++) res += s[f];
        mp[res] = ++tot;
    }
}

vector<node> v;
int main() {
    fast;
    string s; bool f = 0;
    while (getline(cin, s)) {
        if (s == "\\begin{thebibliography}{99}") { f = 1; continue; }
        if (s == "\\end{thebibliography}") break;
        if (!f) find(s);
        else {
            int pos = s.find("\\bibitem{");
            string res;
            for (pos+=9; pos < s.size() && s[pos] != '}'; pos++) res += s[pos];
            v.push_back({mp[res], s});
        }
    }
    bool t = 1;
    rep(i,v.size()) if (v[i].idx != i+1) t = 0;
    if (t) cout << "Correct\n";
    else {
        cout << "Incorrect\n";
        sort(v.begin(), v.end());
        cout << "\\begin{thebibliography}{99}\n";
        for (auto &i : v) cout << i.s << '\n';
        cout << "\\end{thebibliography}\n";
    }
    return 0;
}