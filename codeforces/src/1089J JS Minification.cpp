//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
N = 20 —— 最长的保留字 / 标识符长度上限（解析时最多看 20 个字符）
第一行读入 n。
第二行读入 n 个保留字，全部放入 set<string> rem
第三行读入 m
从位置 st 开始，逐步累积字符 cur，只要 cur 是保留字（在 rem 中），就记录当前匹配长度 res。
返回匹配到的最长保留字长度（最长匹配原则）。遇 #（注释）停止
从 st 开始，连续数字的长度（数字字面量）
若首字符是数字则返回 0（非合法标识符开头）。
否则统计 [字母|数字|_|$] 组成的标识符合法长度
在位置 st 处，取保留字长度、数字长度、标识符长度三者的最大值作为此 token 的切分长度
对每行，从左到右：跳过空格、遇 # 停止、否则用 parse 求出 token 长度并切出存入 ts，然后指针跳到 token 末尾
lst 是一个"下一个小写字母名"的游标，从空开始。
nxt()：按字典序生成下一个小写字符串（a, b, ..., z, aa, ab, ...），并且跳过保留字（rem 中的名字不用）。
对每个非保留字、非数字开头的 token：
若之前没定义过一个新名字，则用 nxt() 分配一个，存入 mp（原名 → 新名映射）。
把 token 替换成新名字。
数字 token 和保留字不做替换。
p 初始为 token 总数（表示"还没有需要合并的分界"）。
对每个 ts[i]，把它后面的 token 逐个拼接成 s：
若 parse(s,0)（从头对整个拼接串解析）‍不等于 ts[i].length()，说明合并后把前面的 token 结构破坏了，于是 p = min(p, j-1) 记录一个分界点，并 break。
若 s 长度超过 N，也 break（不再继续拼）。
输出时：每个 token 之后，若到了分界点 p，则打印一个空格并重置 p
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 20;

int main() {
    fast;
    int n;
    {
        string s; getline(cin, s);
        stringstream ss; ss << s; ss >> n;
    }
    set<string> rem;
    {
        string s; getline(cin, s);
        stringstream ss; ss << s;
        rep(i,n) { string t; ss >> t; rem.insert(t); }
    }
    int m;
    {
        string s; getline(cin, s);
        stringstream ss; ss << s; ss >> m;
    }
    vector<string> ts;
    auto trans = [&](const string &s, const int st) {
        int res = 0;
        string cur;
        for (int i = st; i < st+N && i < s.length() && s[i] != '#'; ++i) {
            cur += s[i];
            if (rem.contains(cur)) res = i - st + 1;
        }
        return res;
    };
    auto trans_no = [&](const string &s, const int st) {
        int res = 0;
        while (st + res < s.length() && isdigit(s[st+res])) ++res;
        return res;
    };
    auto trans_w = [&](const string &s, const int st) {
        if (isdigit(s[st])) return 0;
        int res = 0;
        auto ok = [&](char c) {
            return isdigit(c) || isalpha(c) || c == '_' || c == '$';
        };
        while (st + res < s.length() && ok(s[st+res])) ++res;
        return res;
    };
    auto parse = [&](string &s, int st) {
        return max(max(trans(s,st),trans_no(s,st)),trans_w(s,st));
    };
    while (m--) {
        string s; getline(cin, s);
        rep(i,s.length()) {
            if (s[i] == ' ') continue;
            if (s[i] == '#') break;
            int len = parse(s, i);
            ts.push_back(s.substr(i,len));
            i += len - 1;
        }
    }
    map<string, string> mp; string lst;
    auto nxt = [&]() {
        do {
            int i = lst.length()-1;
            while (~i && lst[i] == 'z') --i;
            if (~i) {
                ++lst[i++];
                while (i < lst.length()) lst[i++] = 'a';
            } else lst = string(lst.length()+1,'a');
        } while (rem.contains(lst));
    };
    for (auto &s : ts) if (!rem.contains(s) && !isdigit(s[0])) {
        if (!mp.contains(s)) { nxt(); mp[s] = lst; }
        s = mp[s];
    }
    int p = ts.size();
    rep(i,ts.size()) {
        string s = ts[i];
        for (int j = i+1; j < ts.size(); ++j) {
            s += ts[j];
            if (parse(s,0) != ts[i].length()) { p = min(p,j-1); break; }
            if (s.length() > N) break;
        }
        cout << ts[i];
        if (i == p) { cout << ' '; p = ts.size(); }
    }
    cout << '\n';
    return 0;
}