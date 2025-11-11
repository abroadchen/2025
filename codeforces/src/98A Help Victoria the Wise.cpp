//
// Created by Psy.C on 2025/11/11.
//
/*
*对f向量进行升序排序
这样相同频次分布的字符串会有相同的排序结果
 *
*声明一个map，键是整数向量（表示排序后的频次分布），值是整数（对应的结果）
用于存储预定义的模式匹配
 *
 *{1,5}表示有一个字符出现1次，另一个字符出现5次，这种情况对应结果1
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {

    string s; getline(cin, s);
    map<char, int> a;
    for (char c : s) a[c]++;

    vector<int> f;
    for (auto& p : a) f.push_back(p.second);
    sort(f.begin(), f.end());

    map<vector<int>, int> res;
    res[{6}] = 1;
    res[{1, 5}] = 1;
    res[{2, 4}] = 2;
    res[{1, 1, 4}] = 2;
    res[{3, 3}] = 2;
    res[{1, 2, 3}] = 3;
    res[{1, 1, 1, 3}] = 5;
    res[{2, 2, 2}] = 6;
    res[{1, 1, 2, 2}] = 8;
    res[{1, 1, 1, 1, 2}] = 15;
    res[{1, 1, 1, 1, 1, 1}] = 30;
    cout << res[f] << '\n';
    return 0;
}