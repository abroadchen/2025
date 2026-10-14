//
// Created by Psy.C on 2026/10/14.
//
/**
a、b：两个临时字符串，用于读取输入。
n、m：数据规模，n 是"表项数"，m 是"查询次数"。
mp：map<string,string>，即有序键值对容器，键和值都是字符串
scanf("%d %d%*c",...)：读入 n、m 两个整数，%*c 表示跳过一个字符（通常吃掉行尾换行符），避免影响后面的 cin。
循环 n 次，每次读入两个字符串 a 和 b，并执行 mp[b] = a——即把 b 作为键，a 作为值存进 map
cin >> a >> b：读入两个字符串。
b.pop_back()：删除 b 的最后一个字符（把 b 缩短一个字符）。
cout << a << ' ' << b << "; #" << mp[b] << '\n'：
输出 a、空格、缩短后的 b；
再输出 ; #；
然后用 mp[b] 查表：用缩短后的 b 作为键，取字典里对应的值输出。
如果 mp 里没有这个键，mp[b] 会插入一个空串并返回它，所以查不到时输出的是空（后面紧接换行）
 */
#include <bits/stdc++.h>
using namespace std;

string a, b;
int n, m;
map<string, string> mp;
int main() {
    scanf ("%d %d%*c", &n, &m);
    for (int i = 0; i < n; ++i) { cin >> a >> b; mp[b] = a; }
    for (int i = 0; i < m; ++i) {
        cin >> a >> b; b.pop_back();
        cout << a << ' ' << b << "; #" << mp[b] << '\n';
    }
    return 0;
}