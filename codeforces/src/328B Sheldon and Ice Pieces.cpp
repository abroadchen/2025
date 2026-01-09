//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char c[8];//数字n的字符串形式
int num[10];//每个数字的可用数量
bool ok() {//当前数字n的字符串形式是否可以用现有的数字组成
    for (int i = 0; i < strlen(c); ++i) {//遍历字符串c的每个字符
        if (num[c[i] - '0'] < 1) return false;//对应数字不够用
        num[c[i] - '0']--;//消耗一个对应数字
    }
    return true;
}

int main() {
    fast;
    int n; cin >> n; char s[1000];
    memset(num, 0, sizeof(num));
    cin >> s; snprintf(c, 8, "%d", n);//将整数n格式化为字符串存入c
    for (int i = 0; i < strlen(c); ++i) {
        if (c[i] == '9') c[i] = '6'; else if (c[i] == '5') c[i] = '2';
    }
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == '9') s[i] = '6'; else if (s[i] == '5') s[i] = '2';
        num[s[i] - '0']++;//统计每个数字的出现次数
    }
    int ans = 0;
    while (true) { if (ok()) ans++; else break; }//如果能组成当前数字，计数加1
    cout << ans << '\n';
    return 0;
}