//
// Created by Psy.C on 2025/9/28.
//
/*
*有n个字符串作为第一组（需要被匹配）
有n个字符串作为第二组（用于匹配）
 *
*如果当前首字母的剩余字符串数等于理论最大匹配数：

必须优先使用相同首字母的字符串进行匹配
选择该首字母对应的最小字符串（set自动排序）
*否则（还有灵活性）：

寻找任意一个还有剩余字符串的首字母类别
选择该类别中最小的字符串
 *
*如果存在相同首字母的字符串，且之前选的字符串首字母大于当前字符串首字母：

改为选择相同首字母的字符串（字典序更优）
 *
*更新状态：

减少第一组该首字母的剩余计数
从第二组中删除已使用的字符串
如果首字母相同，减少该首字母的匹配数上限
 *
*贪心策略：
当必须匹配特定首字母时，优先匹配相同首字母
当有选择余地时，选择字典序较小的字符串
 *
*时间复杂度：O(n log n) 主要由set操作和排序决定
空间复杂度：O(n)
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#define sz(a) (int)a.size()
using namespace std;

int n;
vector<string> v;// 存储第一组字符串
map<char,int> cnt, match;//cnt: 每个首字母的计数, match: 每个首字母的匹配数
map<char,set<string>> S;// 按首字母分类的第二组字符串 使用set自动排序

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for (int i = 0; i < 2*n; ++i) {
        string s; cin>>s;
        if (i < n) v.push_back(s), cnt[s[0]]++;// 前n个字符串属于第一组
        else S[s[0]].insert(s);// 后n个字符串属于第二组，按首字母分类存储
    }
    sort(v.begin(), v.end());
    for (char i = 'A'; i <= 'Z'; ++i) match[i] = min(cnt[i], sz(S[i]));
    for (int i = 0; i < sz(v); ++i) {
        auto s = v[i]; string t("");
        if (cnt[s[0]] == match[s[0]]) t = *S[s[0]].begin();
        else {
            for (char j = 'A'; j <= 'Z'; ++j) {
                if (match[j] < sz(S[j])) {
                    t = *S[j].begin();
                    break;
                }
            }
            if (sz(S[s[0]]) && t[0] > s[0]) t = *S[s[0]].begin();
        }
        cout << s << " " << t;
        if (i != sz(v) - 1) cout << ", ";
        else cout << "\n";
        cnt[s[0]]--;
        S[t[0]].erase(t);
        if (s[0] == t[0]) match[s[0]]--;
    }
    return 0;
}