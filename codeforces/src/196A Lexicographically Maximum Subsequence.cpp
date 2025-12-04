//
// Created by Psy.C on 2025/12/3.
//
/*
 *str[i]是字符，i是该字符在原字符串中的位置
 *如果第一个pair的字符大于第二个pair的字符，则第一个pair排在前面
 *如果第一个pair的字符小于第二个pair的字符，则第一个pair排在后面
 *如果字符相同，则按原始位置升序排列（位置小的排前面）
 *
*如果当前字符在原字符串中的位置大于已选字符的最大位置：
将该字符添加到结果字符串res中
更新j为当前字符的位置
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
#define pci pair<char, int>
using namespace std;


int main() {
    fast;
    string str; cin>>str;
    vector<pair<char, int>> v(sz(str));
    for (int i = 0; i < sz(str); ++i) v[i] = {str[i], i};
    sort(v.begin(), v.end(), [](const pci& a, const pci& b) -> bool {
        if (a.first > b.first) return true;
        if (a.first < b.first) return false;
        return a.second < b.second;
    });
    string res; int j = -1;//已选字符的最大位置
    for (int i = 0; i < sz(v); ++i) {//遍历排序后的vector
        if (v[i].second > j) res += v[i].first, j = v[i].second;
    }
    cout << res << '\n';
    return 0;
}