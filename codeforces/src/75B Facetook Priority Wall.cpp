//
// Created by Psy.C on 2025/11/4.
//
/*
 *定义pair<int, string>的别名pis，用于存储分数和姓名的配对
*自定义比较函数：
首先按分数降序排列（分数高的在前）
如果分数相同，则按姓名升序排列（字母序小的在前）
 *
*声明变量：
n: 操作记录数，k: 分数
na: 目标用户名，in: 输入行，n1,n2: 操作涉及的用户名，a: 操作类型
创建映射：
mp: 存储用户名和对应分数的映射
point: 存储操作类型对应分数的映射（posted=15分，commented=10分，likes=5分）
 *
 *忽略换行符，为后续getline做准备
*创建字符串流ss来解析输入行
读取第一个用户名n1和操作类型a
根据操作类型获取对应分数k
*如果操作不是"likes"，则需要跳过中间的"on"或其他词语
读取第二个用户名n2
 *删除n2末尾的两个字符（通常是逗号","和空格" "）
 *
*如果n1是目标用户na，且n2不是na，则给n2加分
如果n2是目标用户na，则给n1加分
否则只是确保两个用户都在映射中（加分0分）
 *
*创建向量v存储所有用户及其分数
将map中的每个键值对转换为pair<int, string>存入向量
 *
 */
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef pair<int, string> pis;
bool cmp(pis s1, pis s2) {
    if (s1.first != s2.first) return s1.first > s2.first;
    else return s1.second < s2.second;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k;
    string na, in, n1, n2, a;
    map<string, int> mp,
    point{{"posted", 15}, {"commented", 10}, {"likes", 5}};
    cin >> na >> n; cin.ignore();
    while (n--) {
        getline(cin, in);
        istringstream ss(in);
        ss >> n1 >> a;
        k = point[a];
        if (a != "likes") ss >> a;
        ss >> n2;
        n2.pop_back(); n2.pop_back();
        if (n1 == na) {
            if (n2 != na) mp[n2] += k;
        } else if (n2 == na) mp[n1] += k;
        else {
            mp[n1] += 0, mp[n2] += 0;
        }
    }
    vector<pis> v;
    for (auto it : mp) v.push_back({it.second, it.first});
    sort(v.begin(), v.end(), cmp);
    for (auto it : v) cout << it.second << "\n";
    return 0;
}