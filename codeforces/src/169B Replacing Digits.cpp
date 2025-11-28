//
// Created by Psy.C on 2025/11/28.
//
/*
*对字符串s2进行降序排序：
rbegin()和rend()是反向迭代器
这会将s2中的字符按从大到小的顺序排列
 *
 *初始化计数器x = 0，用于跟踪s2中已使用的字符位置
*遍历字符串s1中的每个字符：
如果已经用完了s2中的所有字符，则跳出循环
如果s1中当前字符小于s2中第x个字符（最大的可用字符）：
将s1中的字符替换为s2中第x个字符
计数器x增加1（表示使用了一个字符）
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s1; getline(cin, s1);
    string s2; getline(cin, s2);
    sort(s2.rbegin(), s2.rend());
    int x = 0;
    for (char& i : s1) {
        if (x >= s2.size()) break;
        if (i < s2[x]) { i = s2[x]; ++x; }
    }
    cout << s1 << '\n';
    return 0;
}