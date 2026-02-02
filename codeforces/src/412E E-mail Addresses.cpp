//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
using namespace std;

char s[N];//输入字符串
ll geta(int i) {//从位置 i 向左统计合法标识符字符的数量
    ll num = 0;
    while (i >= 0) {
        if (s[i] >= 'a' && s[i] <= 'z') num++;//遇到小写字母 (a-z) 计数增加
        else if (s[i] != '_' && (s[i] < '0' || s[i] > '9')) break;
        i--;//遇到数字 (0-9) 或下划线 (_) 继续向前
    }
    return num;
}

int len;//字符串的实际长度
ll get(int i) {//从位置 i 向右检查是否存在 "字母数字序列.小写字母序列" 的模式
    ll num = 0;
    const int j = i;
    while (i < len) {
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9'))) break;
        i++;//找到连续的字母数字序列
    }
    if (i >= len || s[i] != '.' || j == i) return 0;
    i++;//检查后面是否紧跟一个点 (.)
    while (i < len) {
        if (s[i] >= 'a' && s[i] <= 'z') num++; else break;//统计点后的小写字母数量
        i++;
    }
    return num;
}


int main() {
    fast;
    cin >> s; len = static_cast<int>(strlen(s));
    int i = 0; ll ans = 0;
    while (i < len) {
        if (s[i] == '@') {//从 @ 左侧向左查找 从 @ 右侧向右查找
            const ll l = geta(i - 1), r = get(i + 1);
            ans += l * r;
        }
        i++;
    }
    cout << ans << '\n';
    return 0;
}