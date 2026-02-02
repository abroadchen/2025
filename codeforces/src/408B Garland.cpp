//
// Created by Psy.C on 2026/2/2.
//
/**
* 时间复杂度：O(|a| + |b|)
空间复杂度：O(字符集大小)
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string a, b; cin >> a >> b;
    map<char, int> mp, mq;
    for (auto x : a) mp[x]++;//统计字符串a中各字符出现次数
    for (auto x : b) mq[x]++;
    int res = 0;
    for (auto [fst, snd] : mq) {
        if (mp[fst] == 0)  { res = 0; break; }//字符fst在a中不存在（频次为0）
        res += min(snd, mp[fst]);//该字符的最大匹配数
    }
    if (!res) cout << "-1"; else cout << res;
    return 0;
}