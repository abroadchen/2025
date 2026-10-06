//
// Created by Psy.C on 2026/10/6.
//
/**
维护了一个名字数组，共 5 个：Danil、Olya、Slava、Ann、Nikita。
s 是待匹配的输入字符串
对每个名字 i，在字符串 s 的每个位置 j 取长度等于 i.size() 的子串，若与名字相等则 flg++。
即统计这 5 个名字在 s 中（作为连续子串）出现的总次数。注意：
同一名字在多个位置出现会各计一次。
名字之间可能重叠也会分别计入（因为每次独立比较，如 s="Nikita" 中 Nikita 出现一次；Ann 单独出现等）
若这 5 个名字总共恰好出现 1 次，输出 YES；否则（0 次、2 次及以上）输出 NO。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string str[] = {
    "Danil", "Olya", "Slava", "Ann", "Nikita"
}, s;
int main() {
    fast;
    cin >> s;
    int flg = 0;
    for (const auto& i : str)
        for (int j = 0; j < s.size(); ++j)
            if (s.substr(j, i.size()) == i) flg++;
    if (flg == 1) cout << "YES\n"; else cout << "NO\n";
    return 0;
}