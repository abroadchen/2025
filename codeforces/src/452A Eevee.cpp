//
// Created by Psy.C on 2026/2/10.
//
/**
n：输入字符串长度
len[]：8个宝可梦名称的长度数组
ans：匹配成功的宝可梦索引
s[20]：输入的模糊字符串（最大20字符）
m[]：8个宝可梦名称数组

时间复杂度：O(8 × max_length) = O(1)，常数时间
空间复杂度：O(1)，只使用固定大小的数据结构
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, len[] = {8, 7, 7, 6, 7, 7, 7, 7}, ans;
char s[20];
string m[] = {
    "vaporeon","jolteon","flareon","espeon",
    "umbreon","leafeon","glaceon","sylveon"
};

int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < 8; ++i) {
        if (len[i] == n) {//长度是否匹配
            int flag = 0;
            for (int j = 0; j < n; ++j) {
                //不是通配符'.' 且不等于对应宝可梦的字符
                if (s[j] != '.' && s[j] != m[i][j]) {
                    flag = 1; break;
                }
            }
            if (flag == 0) { ans = i; break; }
        }
    }
    cout << m[ans] << '\n';
    cout << '\n';
    return 0;
}