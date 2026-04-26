//
// Created by Psy.C on 2026/4/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4;
char s[N], r[N];
int len;
int main() {
    fast;
    cin >> len >> s;
    //i是遍历原字符串的索引，num是构建结果字符串的索引
    for (int i = 0, num = 0; i < len; ) {
        //检查当前位置是否匹配"ogo"模式
        if (s[i] == 'o' && s[i+1] == 'g' && s[i+2] == 'o') {
            i += 3;//将索引向前移动3位
            //查找连续的"go"模式，如果找到就继续跳过，直到找不到为止
            while (true) {
                if (s[i] == 'g' && s[i+1] == 'o') i += 2;
                else break;
            }
            //将匹配到的整个模式串 替换为三个星号***
            r[num++] = '*';
            r[num++] = '*';
            r[num++] = '*';
        } else {//如果不匹配"ogo"模式，则将当前字符复制到结果数组中
            r[num++] = s[i];
            i++;
        }
    }
    cout << r << '\n';
    return 0;
}