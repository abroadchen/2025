//
// Created by Psy.C on 2026/10/19.
//
/**
字符串长度小于 4 直接判 No。说明题目要求至少 4 个字符（可能是"四字母才能满足某种结构"）
遍历字符串，用 mp 记录每个字符出现次数；某字符第一次出现时 cnt++，得到不同字符种类数
种类数 ≤1 或 ≥5 直接 No。所以合法种类数只能是 2、3、4
若有 2 种字符，循环所有字符的出现次数，只要有任何一种出现次数为 1 就判 No。

用 views::values（C++20 ranges，取 map 的 value 视图）遍历所有频次。意思是：当只有 2 种字符时，两种都必须出现 ≥2 次（即 val != 1，因为 map 里每个 value 至少是 1，出现次数为 1 就不合格）。换句话说 2 种字符时，要求每种都至少出现 2 次
若有 3 种字符：遍历频次，只要存在某一种出现次数 >1 就置 flg=1。若 没有任何一种 >1（即三种都各出现 1 次）则判 No。

即：3 种字符时，必须至少存在一种出现 ≥2 次（不能三种都只出现 1 次）
4 种字符直接放行输出 Yes（前面 ≥5 已排除，所以这里 cnt==4 是唯一通过全部条件的）
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

string s;
map<char, int> mp;
int main() {
    fast;
    cin >> s;
    if (s.size() < 4) { cout << "No"; return 0; }
    int cnt = 0;
    for (char i : s) {
        mp[i]++;
        if (mp[i] == 1) cnt++;
    }
    if (cnt <= 1 || cnt >= 5) { cout << "No"; return 0; }
    if (cnt == 2) {
        for (auto val: mp | views::values) {
            if (val == 1) { cout << "No"; return 0; }
        }
    }
    if (cnt == 3) {
        bool flg = 0;
        for (auto val: mp | views::values) if (val > 1) flg = 1;
        if (flg == 0) { cout << "No"; return 0; }
    }
    cout << "Yes";
    return 0;
}