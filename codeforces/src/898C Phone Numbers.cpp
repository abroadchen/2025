//
// Created by Psy.C on 2026/10/10.
//
/**
用 map 把每个 s 映射到一个 set<string>。set 自带去重 + 排序，所以每个名字下的字符串集合是唯一的、按字典序排列
对组内每个字符串 a，检查是否存在另一个更长的字符串 b，满足：

b 的长度 > a 的长度
b 的末尾（即后缀）恰好等于 a（b 以 a 结尾）
如果存在这样的 b，说明 a 是某个更长串的后缀，就把 a 标记为 flg = true，不输出；否则保留进 v。

换句话说：一个元素如果自己是组内另一个更长元素的"结尾"，就被剔除；只保留那些「没有更长的元素以它结尾」的串
第一行输出名字总数（map 里 s 的去重数量），随后每个名字输出：名字、精简后的元素个数、以及这些保留的元素（空格分隔）
对每个名字，内部是两重遍历 set，复杂度
O
(
K
2
)
O(K
2
 )（K 为该名字下元素数），最坏情况下若所有元素都在一个名字下会较慢
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    while (cin >> n) {
        map<string, set<string>> mp;
        for (int i = 0; i < n; ++i) {//每个名字 s 下有 num 个字符串 t，全部塞入对应的 set
            string s; int num; cin >> s >> num;
            for (int j = 0; j < num; ++j) {
                string t; cin >> t;
                mp[s].insert(t);
            }
        }
        cout << mp.size() << '\n';
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            string nm = it->first;
            vector<string> v;
            for (auto it2 = mp[nm].begin(); it2 != mp[nm].end(); ++it2) {
                bool flg = false;
                const string& a = *it2;
                for (const auto& b : mp[nm]) {
                    if (a == b) continue;
                    if (b.length() > a.length() &&
                        b.substr(b.length()-a.length(), a.length()) == a) {
                        flg = true; break;
                    }
                }
                if (flg == false) v.push_back(a);
            }
            cout << nm << ' ' << v.size() << ' ';
            for (const auto& i : v) cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}