//
// Created by Psy.C on 2026/3/13.
//
/**
len：字符串长度
num：操作次数
t：操作位置
s[N]：存储字符串
c：要替换的字符

初始化连续点对的数量为0
遍历字符串，统计初始状态下相邻的两个'.'的对数

如果原字符是小写字母，要替换成'.'
检查左边相邻字符：如果是'.'，ans++
检查右边相邻字符：如果是'.'，ans++
如果原字符是'.'，要替换成字母
检查左边相邻字符：如果是'.'，ans--
检查右边相邻字符：如果是'.'，ans--
更新字符串位置t-1的字符为c
输出当前连续点对的数量
循环处理下一个操作

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;
int len, num, t;
char s[N], c;
int main() {
    fast;
    cin >> len >> num >> s;
    int ans = 0;
    for (int i = 0; i < len - 1; ++i) {
        if (s[i] == '.')
            if (s[i+1] == '.') ans++;
    }
    while (num--) {
        cin >> t >> c;
        if (s[t-1] >= 'a' && s[t-1] <= 'z') {
            if (c == '.') {
                if (s[t-2] == '.') ans++;
                if (s[t] == '.') ans++;
            }
        }
        if (s[t-1] == '.') {
            if (c >= 'a' && c <= 'z') {
                if (s[t-2] == '.') ans--;
                if (s[t] == '.') ans--;
            }
        }
        s[t-1] = c;
        cout << ans << '\n';
    }
    return 0;
}