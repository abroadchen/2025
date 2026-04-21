//
// Created by Psy.C on 2026/4/20.
//
/**
ord[2]：字符数组，存储操作符（+、-、？）
str[20]：字符数组，存储输入的二进制字符串（最多20位）
st为0，用于存储转换后的十进制数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
map<int, int> mp;//二进制字符串转换后的十进制数值及其出现次数
char ord[2], str[20];
int main() {
    fast;
    cin >> n;
    while (n--) {
        cin >> ord >> str;
        int st = 0, len = strlen(str);
        for (int i = 0; i < len; ++i) {//将二进制字符串转换为对应的十进制数
            st <<= 1;
            if (str[i] % 2 == 1) st |= 1;//如果是奇数则在最低位置1
        }
        if (ord[0] == '+') mp[st]++;
        else if (ord[0] == '-') {
            mp[st]--;
            if (mp[st] == 0) mp.erase(st);
        } else cout << mp[st] << '\n';//当前数值的计数
    }
    return 0;
}