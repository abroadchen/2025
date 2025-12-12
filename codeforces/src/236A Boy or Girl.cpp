//
// Created by Psy.C on 2025/12/12.
//
/*
*声明大小为26的整型数组a，初始化为全0（用于统计每个字母出现次数）
a[0]对应字母'a'，a[1]对应'b'，...，a[25]对应'z'
声明整型变量ans并初始化为0（用于统计不同字母的总数）
 *
*使用范围for循环遍历字符串s中的每个字符
i - 'a'将字符转换为对应的数组索引（'a'->0, 'b'->1, ..., 'z'->25）
对应字母的计数器加1
 *
*遍历计数数组a中的每个元素
如果某个字母的计数i不为0（即该字母在字符串中出现过），则ans加1
最终ans存储了字符串中不同字母的总数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin>>s;
    int a[26] = {}, ans = 0;
    for (const char i : s) a[i - 'a']++;
    for (const int i : a) if (i) ans++;
    if (ans & 1) cout << "IGNORE HIM!" << '\n';
    else cout << "CHAT WITH HER!" << '\n';
    return 0;
}