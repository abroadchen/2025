//
// Created by Psy.C on 2026/1/22.
//

#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int get(vector<char> v) {
    int c = 1, mx = 0;//当前连续相同字符计数器 最大连续相同字符数
    ranges::sort(v);//按字母序排序
    int p = static_cast<unsigned char>(v[0]);//第一个字符
    for (int i = 1; i < v.size(); ++i) {
        //如果当前字符与前一个不同，更新p为当前字符，重置c为0
        if (v[i] != p) { p = static_cast<unsigned char>(v[i]); c = 0; }
        c++;//当前连续相同字符数加1
        mx = max(mx, c);
    }
    return mx;
}

int main() {
    fast;
    int k; cin >> k;
    vector<char> v;
    string s;
    for (int i = 0; i < 4; ++i) {
        cin >> s;
        for (int j = 0; j < 4; ++j) {//遍历每行的4个字符
            if (s[j] == '.') continue;
            v.push_back(s[j]);
        }
    }
    if (v.empty()) { cout << "YES"; return 0; }
    const int mx = get(v);
    mx <= k<<1 ?  cout << "YES" : cout << "NO";
    return 0;
}