//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
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
    while ((pos = s.find("\\cite{", f) != -1)) {
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