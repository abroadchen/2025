//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<string> str; str.resize(n + 1);//字符串动态数组
    for (int i = 1; i <= n; ++i) cin >> str[i];
    const int len = static_cast<int>(str[1].size());//第一个字符串的长度作为基准长度
    string res;//存储最终合并后的结果
    for (int i = 0; i <= len-1; ++i) {//遍历每个字符位置
        char c = str[1][i];//第一个字符串在位置 i 的字符作为初始值
        bool flag = true;//当前字符位置是否一致
        for (int j = 2; j <= n; ++j) {//从第二个字符串开始，逐一比较所有字符串在位置 i 的字符
            if (c == '?') c = str[j][i]; else {//用当前字符串的字符替换它
                //当前字符与待比较字符相同，或者待比较字符是 ?
                if (c == str[j][i] || str[j][i] == '?') continue;
                flag = false;//两个字符不同且都不是 ?
                break;
            }
        }
        if (!flag) res.push_back('?');
        else res.push_back(c == '?' ? 'x' : c);
    }
    cout << res << '\n';
    return 0;
}