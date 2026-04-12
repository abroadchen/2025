//
// Created by Psy.C on 2026/4/13.
//
/**
将字符t插入到s2中某个位置后，是否会使得新字符串的字典序变大
检查字符t是否大于字符串s2的对应位置
遍历s2的每个字符，如果遇到不相等的情况，返回t是否大于s2[i]
如果s2中所有字符都等于t，则返回false

遍历s1，统计每个数字字符的出现次数
寻找一个数字，其位数等于剩余长度
循环尝试不同长度i（1到7）
num = len - i：剩余长度
tt：计算num的位数
如果num的位数等于i，则找到了合适的数字
将数字nw的每一位从计数数组中减去
从个位开始，逐位处理

将s2中每个字符对应的计数减1
ok: 记录第一个使用的数字
flag: 标记是否已经处理过
a1, a2: 两个结果字符串
将s2添加到a2中
从数字1开始查找第一个可用的数字
添加到a1中，更新ok和计数数组
遍历0-9每个数字
如果当前数字是ok，则添加到a2
如果还没有标记且满足check条件，将s2添加到a1
将剩余的数字添加到a1和a2中

如果没有找到可用数字，输出a2
否则：
如果没有标记过，将s2添加到a1
如果a2以0开头，输出a1
否则输出a1和a2的字典序较小者

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

char s1[N], s2[N];
bool check(char t, int len) {
    for (int i = 1; i <= len; ++i)
        if (s2[i] != t)
            return t > s2[i];
    return false;
}

int cnt[10];
int main() {
    fast;
    scanf("%s", s1 + 1);
    int len = strlen(s1 + 1);
    for (int i = 1; i <= len; ++i) cnt[s1[i]-'0']++;
    int nw = 0;
    for (int i = 1; i <= 7; ++i) {
        int num = len - i, tt = 0;
        while (num) { tt++; num/=10; }
        if (tt == i) { nw = len - i; break; }
    }
    while (nw) {
        cnt[nw%10]--; nw/=10;
    }
    scanf("%s", s2 + 1); len = strlen(s2 + 1);
    for (int i = 1; i <= len; ++i) cnt[s2[i]-'0']--;
    int ok = -1; bool flag = false; string a1, a2;
    a2 += s2 + 1;
    for (int i = 1; i <= 9; ++i)
        if (cnt[i] > 0) {
            a1 += char(i + '0');
            ok = i; cnt[i]--; break;
        }
    for (int i = 0; i <= 9; ++i) {
        char t = i + '0';
        if (ok == i) a2 += t;
        if (!flag && check(t, len)) {
            a1 += s2 + 1;
            flag = true;
        }
        while (cnt[i]) { a1 += t; a2 += t; cnt[i]--; }
    }
    if (ok == -1) cout << a2.c_str() << '\n';
    else {
        if (!flag) a1 += s2;
        if (a2[0] == '0') cout << a1.c_str() << '\n';
        else cout << min(a1, a2).c_str() << '\n';
    }
    return 0;
}